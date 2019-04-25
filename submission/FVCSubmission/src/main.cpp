#include <iostream>
#include "FvcHeader.h"
#include "MRKFile.h"

int main(int argc, char *argv[]) 
{
	MRKFile *mrkFile = new MRKFile();
	std::cout << mrkFile->toString() << std::endl;

	return 0;
}