
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "file_reader.h"


FileReader::FileReader() {}
FileReader::~FileReader() {}

std::vector<std::vector<int>> FileReader::read(std::string path) {
    std::vector<std::vector<int>> lines;
    std::ifstream file; 
    file.open(path.c_str());

    if (!file.is_open()) std::cout << "Erro ao abrir o arquivo!\n";
    
    int a, b, c;
    while (file >> a >> b >> c) {
        lines.push_back(std::vector<int>());
        lines.back().push_back(a);
        lines.back().push_back(b);
        lines.back().push_back(c);
    }

    return lines;
}
