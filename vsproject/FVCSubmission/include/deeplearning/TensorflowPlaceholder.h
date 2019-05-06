#pragma once

#ifndef TENSORFLOW_PLACEHOLDER_H
#define TENSORFLOW_PLACEHOLDER_H

using namespace tensorflow;

namespace deeplearning
{
	class TensorflowPlaceholder
	{
	public:
		typedef std::pair<std::string, Tensor> placeholderType;
		typedef std::vector<placeholderType> tensorDict;
		
		static placeholderType tensor(string key, Tensor t)
		{
			return { key, t };
		}

		static placeholderType boolean(string key, bool value)
		{
			Tensor placeholder(DT_BOOL, TensorShape());
			placeholder.scalar<bool>()() = value;
			return { key, placeholder };
		}
	};
}

#endif