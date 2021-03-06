// consolePcapNg.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "libPcapNgDLL.h"

// Convert single char to (unsigned) int
int char2int(char input) {
	int output;
	(int)input < 0 ? output = input + 256 : output = input;
	return output;
}

int main()
{
	std::string fileName;
	std::cout << "Type the input file name: ";
	std::cin >> fileName;
	std::string version;
	char* currentPacket;
	int widthIPpacket;

	LibPcapNg::FileManagement *file = new LibPcapNg::FileManagement(fileName);
	version = file->getVersion(); 
	std::cout << "DLL version: " << version << std::endl;
	if (file->Load() == false) {
		std::cout << "Error during loading of the file " << fileName << std::endl; 
		return -1;
	}
	
	if (file->parsePcapNG("10.0.5.7", "10.0.5.5", 20000, 20000) == false) {
		std::cout << "Error during the parsing of the pcap file" << std::endl;
		return -2;
	}

	currentPacket = file->getFirstPacket();
	while (currentPacket != NULL) {
		widthIPpacket = file->getBSDSize();
		for (int cpt = 0; cpt < widthIPpacket; cpt+=1) { std::cout << std::hex << char2int(currentPacket[cpt]) << " "; }
		std::cout << std::endl;
		currentPacket = file->getNextPacket();
	}
	std::cin >> version;
	delete file;

	return 0;
}

