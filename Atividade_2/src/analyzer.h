
#include <iostream>
#include "analyzer.cpp"


void Analyzer::analyze(std::size_t frames, std::size_t references, std::size_t pfs_fifo, std::size_t pfs_lru, std::size_t pfs_opt) {

    // Mudar para map o pfs?
    std::cout << frames << " quadros\n";
    std::cout << references << " refs\n";
    std::cout << "FIFO: " << pfs_fifo << " PFs\n";
    std::cout << "LRU: " << pfs_lru << " PFs\n";
    std::cout << "OPT: " << pfs_opt << " PFs\n";

}

