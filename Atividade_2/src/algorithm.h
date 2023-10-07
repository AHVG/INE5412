#ifndef _H_ALGORITHM
#define _H_ALGORITHM

#include <iostream>
#include <queue>

#include "page.h"

class Algorithm {

protected:

    std::size_t RAMFrames;

public:

    Algorithm();
    Algorithm(std::size_t _RAMFrames);
    
    virtual ~Algorithm();

    virtual int accessMemory(std::size_t page) = 0;

};


class FifoAlgorithm : public Algorithm{

private:

    std::queue<Page> pages;

public:

    FifoAlgorithm();
    FifoAlgorithm(std::size_t _RAMFrames);

    ~FifoAlgorithm();

    int accessMemory(std::size_t page);

};

#endif