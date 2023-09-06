
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "file_reader.h"


FileReader::FileReader() {}
FileReader::~FileReader() {}

std::vector<std::string> FileReader::read(std::string path) {
    std::vector<std::string> lines;
    std::ifstream file; 
    file.open(path.c_str());

    if (!file.is_open()) std::cout << "Erro ao abrir o arquivo!\n";
    
    std::string a, b, c;
    while (file >> a >> b >> c) lines.push_back(a + b + c);

    return lines;
}
