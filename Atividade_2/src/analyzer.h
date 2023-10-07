#ifndef _H_ANALYZER
#define _H_ANALYZER

#include <iostream>

class Analyzer {

public:

    void analyze(std::size_t frames, std::size_t references, std::size_t pfsFIFO, std::size_t pfsLRU, std::size_t pfsOPT);

};

#endif
