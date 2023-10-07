
#include <iostream>
#include "analyzer.h"


void Analyzer::analyze(std::size_t frames, std::size_t references, std::size_t pfsFifo, std::size_t pfsLru, std::size_t pfsOpt) {

    // Mudar para map o pfs?
    std::cout << frames << " quadros\n";
    std::cout << references << " refs\n";
    std::cout << "FIFO: " << pfsFifo << " PFs\n";
    std::cout << "LRU: " << pfsLru << " PFs\n";
    std::cout << "OPT: " << pfsOpt << " PFs\n";

}
