#ifndef _H_ALGORITHM
#define _H_ALGORITHM

#include <iostream>
#include <vector>

#include "page.h"

class ReplacementAlgorithm {

protected:

    std::size_t RAMFrames;

public:

    ReplacementAlgorithm();
    ReplacementAlgorithm(std::size_t _RAMFrames);
    
    virtual ~ReplacementAlgorithm();

    virtual int accessMemory(std::size_t page) = 0;

};


class FifoAlgorithm : public ReplacementAlgorithm {

private:

    std::vector<Page> pages;

public:

    FifoAlgorithm();
    FifoAlgorithm(std::size_t _RAMFrames);

    ~FifoAlgorithm();

    int accessMemory(std::size_t page);

};

#endif