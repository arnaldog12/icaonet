#pragma once

#ifndef TENSORFLOW_GRAPH_H
#define TENSORFLOW_GRAPH_H

#include "TensorflowUtils.h"
#include "TensorflowPlaceholder.h"

using namespace tensorflow;
using deeplearning::TensorflowUtils;
using deeplearning::TensorflowPlaceholder;

namespace deeplearning
{
	class TensorflowGraph
	{
	private:
		Session *session;
		

	public:
		TensorflowGraph(std::string metaFile, std::string checkpointFolder, SessionOptions options = SessionOptions()) 
		{
			MetaGraphDef graphDef = this->loadGraphFromMetaFile(metaFile);
			this->session = this->createSession(graphDef.graph_def(), options);
			loadCheckpoint(graphDef, checkpointFolder);
		}

		TensorflowGraph(std::string protobufFile, SessionOptions options = SessionOptions())
		{
			GraphDef graphDef = this->loadGraphFromProtobufFile(protobufFile);
			this->session = this->createSession(graphDef, options);
		}

		TensorflowGraph(std::ostringstream& protobufFile, SessionOptions options = SessionOptions())
		{
			std::string decoded = protobufFile.str();
			GraphDef graphDef = this->loadGraphFromString(decoded);
			this->session = this->createSession(graphDef, options);
		}

		~TensorflowGraph() 
		{
			tensorflow::Status status =	this->session->Close();
			delete this->session;
		}

		std::vector<std::vector<cv::Mat>> run(TensorflowPlaceholder::tensorDict feedDict, std::vector<std::string> outputTensorNames, std::vector<std::string> targetNodeNames = {})
		{
			std::vector<Tensor> outputsTensor;
			TF_CHECK_OK(session->Run(feedDict, outputTensorNames, targetNodeNames, &outputsTensor));
			return TensorflowUtils::tensor2mat(outputsTensor);
		}

	private:
		MetaGraphDef loadGraphFromMetaFile(std::string metaFile)
		{
			MetaGraphDef graphDef;
			TF_CHECK_OK(ReadBinaryProto(Env::Default(), metaFile, &graphDef));
			return graphDef;
		}

		GraphDef loadGraphFromProtobufFile(std::string protobufFile)
		{
			GraphDef graphDef;
			TF_CHECK_OK(ReadBinaryProto(Env::Default(), protobufFile, &graphDef));
			return graphDef;
		}

		GraphDef loadGraphFromString(std::string protobufFile)
		{
			GraphDef graphDef;
			if (!graphDef.ParseFromString(protobufFile)) throw "Nao foi possible carregar o modelo do Tensorflow!";
			return graphDef;
		}

		Session* createSession(GraphDef graphDef, SessionOptions options)
		{
			Session *session;
			TF_CHECK_OK(NewSession(options, &session));
			TF_CHECK_OK(session->Create(graphDef));
			return session;
		}

		void loadCheckpoint(MetaGraphDef& graphDef, std::string checkpointFolder)
		{
			Tensor checkpointPathTensor(DT_STRING, TensorShape());
			checkpointPathTensor.scalar<std::string>()() = checkpointFolder;
			TF_CHECK_OK(
				session->Run(
					{ { graphDef.saver_def().filename_tensor_name(), checkpointPathTensor } },
					{},
					{ graphDef.saver_def().restore_op_name() },
					nullptr)
			);
		}
	};
}

#endif