#ifndef _H_FILE_READER
#define _H_FILE_READER

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class FileReader
{

private:

public:
	FileReader() {}
	~FileReader() {}
	
	std::vector<std::string> read(std::string path) {
		std::vector<std::string> lines;
		std::ifstream file; 
		file.open(path.c_str());
	
		if (!file.is_open()) std::cout << "Erro ao abrir o arquivo!\n";
		
		std::string a, b, c;
		while (file >> a >> b >> c) lines.push_back(a + b + c);

		return lines;
	}

};

#endif