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
		std::ifstream file; 
		file.open(path.c_str());
	
		if (!file.is_open()) std::cout << "Erro ao abrir o arquivo!\n";
		
		int a, b, c;
		while (file >> a >> b >> c) std::cout << a << b << c << std::endl;

	}

};

#endif