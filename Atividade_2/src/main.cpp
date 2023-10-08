#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "replacementAlgorithm.h"
#include "analyzer.h"


int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <frames>" << std::endl;
        return 1;
    }

    std::size_t frames = std::atoi(argv[1]);
    std::size_t numberOfLines = 0;
    std::size_t pfsFIFO = 0;
    std::size_t pfsLRU = 0;
    std::size_t pfsOPT = 0;

    std::string line;

    FIFOAlgorithm fifo(frames);
    LRUAlgorithm lru(frames);
    Analyzer analyzer;

    while (std::cin >> line) {
        std::size_t pageId = std::stoi(line);
        pfsFIFO += !fifo.accessMemory(pageId);
        pfsLRU += !lru.accessMemory(pageId);
        pfsOPT += 0;
        numberOfLines += 1;
    }

    analyzer.analyze(frames, numberOfLines, pfsFIFO, pfsLRU, pfsOPT);

    return 0;
}