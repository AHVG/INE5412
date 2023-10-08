#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "replacementAlgorithm.h"
#include "analyzer.h"

#include <vector>
#include <algorithm>
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
    OPTAlgorithm opt(frames);

    Analyzer analyzer;
    
    std::vector<std::size_t> lines;

    while (std::cin >> line) {
        lines.push_back(static_cast<size_t>(std::stoi(line)));
    }

    for (std::size_t i = 0; i < lines.size(); i++){
        std::size_t pageId = lines[i];
        pfsFIFO += !fifo.accessMemory(pageId);
        pfsLRU += !lru.accessMemory(pageId);
        if (opt.full())
            //TODO: se a lista estiver cheia e o elemento que eu quiser inserir ja esta na lista, ele nao precisaria chamar o refreshTags
            opt.refreshTags(lines, i);
        pfsOPT += !opt.accessMemory(pageId);
        numberOfLines = lines.size();
    }

    analyzer.analyze(frames, numberOfLines, pfsFIFO, pfsLRU, pfsOPT);

    return 0;
}