#ifndef _H_ANALYZER
#define _H_ANALYZER

#include <iostream>

class Analyzer {

public:

    void analyze(std::size_t frames, std::size_t references, std::size_t pfs_fifo, std::size_t pfs_lru, std::size_t pfs_opt);

};

#endif
