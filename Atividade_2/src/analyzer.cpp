
#include <iostream>
#include "analyzer.h"


void Analyzer::analyze(std::size_t frames, std::size_t references, std::size_t pfsFIFO, std::size_t pfsLRU, std::size_t pfsOPT) {

    // Mudar para map o pfs?
    std::cout << frames << " quadros\n";
    std::cout << references << " refs\n";
    std::cout << "FIFO: " << pfsFIFO << " PFs\n";
    std::cout << "LRU: " << pfsLRU << " PFs\n";
    std::cout << "OPT: " << pfsOPT << " PFs\n";

}
