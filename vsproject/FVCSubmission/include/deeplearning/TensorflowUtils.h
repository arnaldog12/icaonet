#pragma once

#ifndef TENSORFLOW_UTILS_H
#define TENSORFLOW_UTILS_H

#include "opencv2/core/core.hpp"
#include "tensorflow/core/public/session.h"
#include "tensorflow/core/protobuf/meta_graph.pb.h"

using namespace tensorflow;

typedef enum
{
	TENSOR_2D = 1,
	TENSOR_4D = 3,
}TENSOR_SHAPE;

namespace deeplearning
{
	class TensorflowUtils
	{
	public:
		template <class T>
		static Tensor mat2tensor(cv::Mat image, tensorflow::DataType type = tensorflow::DT_FLOAT, TENSOR_SHAPE shape = TENSOR_4D, int nImages = 1)
		{
			T *imageData = (T *)image.data;
			TensorShape imageShape;
			switch (shape)
			{
				case TENSOR_2D: imageShape = TensorShape{ nImages, image.rows * image.cols * image.channels() / nImages }; break;
				default: imageShape = TensorShape{ nImages, image.rows / nImages, image.cols, image.channels() }; break;
			}
			Tensor imageTensor = Tensor(type, imageShape);
			std::copy_n((char *)imageData, imageShape.num_elements() * sizeof(T), const_cast<char *>(imageTensor.tensor_data().data()));
			return imageTensor;
		}

		template <class T>
		static Tensor mat2tensor(std::vector<cv::Mat> images, tensorflow::DataType type = tensorflow::DT_FLOAT, TENSOR_SHAPE shape = TENSOR_4D)
		{
			cv::Mat imagesConcat;
			cv::vconcat(images, imagesConcat);
			return mat2tensor<T>(imagesConcat, type, shape, images.size());
		}

		static std::vector<cv::Mat> tensor2mat(Tensor tensor)
		{
			TensorShape shape = tensor.shape();
			int nDims = shape.dims();

			int nImages = (int) shape.dim_size(0);
			int width  = (int) (nDims > 2 ? shape.dim_size(2) : (nDims > 1 ? shape.dim_size(1) : shape.dim_size(0)));
			int height = (int) (nDims > 2 ? shape.dim_size(1) : 1);
			int channels = (nDims == 4) ? (int) shape.dim_size(3) : 1;

			std::vector<cv::Mat> result;
			for (int i = 0; i < nImages; i++)
			{
				Tensor slice = tensor.Slice(i, i + 1);
				assert(slice.IsAligned() == true);

				float *outputData = slice.flat<float>().data();
				cv::Mat imgOut(cv::Size(width, height), CV_32FC(channels));
				std::copy_n((char*)outputData, slice.shape().num_elements() * sizeof(float), (char*)imgOut.data);
				result.push_back(imgOut);
			}

			return result;
		}

		static std::vector<std::vector<cv::Mat>> tensor2mat(std::vector<Tensor> tensors)
		{
			std::vector<std::vector<cv::Mat>> results;
			for (Tensor t : tensors)
				results.push_back(tensor2mat(t));
			return results;
		}
	};
}

#endif
