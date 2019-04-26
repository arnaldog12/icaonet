#pragma once

#include <string>

class FileUtils
{
public:
	static std::string getFileName(std::string file, bool returnExtension = true)
	{
		size_t last_slash, last_point;
		last_slash = file.find_last_of("\\");
		last_point = file.find_last_of(".");
		return file.substr(last_slash + 1, returnExtension ? std::string::npos : last_point - last_slash - 1);
	}

	static std::string getFileExtension(std::string file, bool returnDot = true)
	{
		size_t last_dot = file.find_last_of(".");
		return file.substr(returnDot ? last_dot : last_dot + 1);
	}
};