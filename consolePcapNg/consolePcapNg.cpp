// consolePcapNg.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "libPcapNgDLL.h"

int main()
{
	std::string fileName;
	std::cout << "Type the input file name: ";
	std::cin >> fileName;
	std::string version;
	char* currentPacket;

	LibPcapNg::FileManagement *file = new LibPcapNg::FileManagement(fileName);
	version = file->getVersion(); 
	std::cout << "DLL version: " << version << std::endl;
	if (file->Load() == false) {
		std::cout << "Error during loading of the file " << fileName << std::endl; 
		return -1;
	}
	currentPacket = file->getFirstPacket();
	while (currentPacket != NULL) { 
		std::cout << currentPacket;
		currentPacket = file->getNextPacket();
	}
	delete file;

	return 0;
}

