#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#include "analyzer.h"
#include "replacementAlgorithm.h"


int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <frames>" << std::endl;
        return 1;
    }

    int frames = std::atoi(argv[1]);
    std::vector<int> referencias;

    std::cout << "Number of RAM frames: " << frames << "\n\n";
    std::cout << "File content (./entradas/entrada.txt): " << "\n\n";
    
    FifoAlgorithm algo(frames);
    size_t misses = 0;
    std::string line;
    // int numberOfLine = 0;

    // Trocar por !(feof(std::stdin) = line)?
    while (std::cin >> line) {
        // std::cout << std::setw(5) << numberOfLine + 1 << ": " << line << "\n";
        // numberOfLine++;
        misses += algo.accessMemory(std::stoi(line));
    }
    std::cout << misses << std::endl;

    // Entrada vsim-belady não corresponde ao que está no documento possívelmente
    // TODO: Testar novametne para o algoritmo FIFO
    // Analyzer analyzer;
    // analyzer.analyze(frames, numberOfLine, 17, 15, 11);


    return 0;
}