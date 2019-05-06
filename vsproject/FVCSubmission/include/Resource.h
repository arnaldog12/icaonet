// BioPassFile.h
// Criado em 11/10/2018 por Arnaldo Gualberto
//

#ifndef UTILS_RESOURCE_H_
#define UTILS_RESOURCE_H_

#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

typedef enum
{
	MODEL_HATCAP = 101
}RESOURCE_ID;

class Resource 
{
private:
	HRSRC hResource = nullptr;
	HGLOBAL hMemory = nullptr;
	void* ptr = nullptr;
	std::size_t size_bytes;

public:
	Resource(int resource_id, const std::string &resource_class = "TEXT") 
	{
		hResource = FindResourceA(nullptr, MAKEINTRESOURCEA(resource_id), resource_class.c_str());
		hMemory = LoadResource(nullptr, hResource);

		this->size_bytes = SizeofResource(nullptr, hResource);
		this->ptr = LockResource(hMemory);
	}

	void* getResource() const 
	{
		return this->ptr;
	}

	int getSizeBytes() const
	{
		return static_cast<int>(this->size_bytes);
	}

	std::string asString() const
	{
		std::string content;
		if (this->ptr != nullptr)
			content = std::string(reinterpret_cast<char*>(ptr), size_bytes);
		return content;
	}
};

#endif