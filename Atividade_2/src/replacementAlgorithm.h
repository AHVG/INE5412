#ifndef _H_ALGORITHM
#define _H_ALGORITHM

#include <iostream>
#include <vector>

#include "page.h"

class ReplacementAlgorithm {

protected:

    std::size_t RAMFrames;
    std::vector<Page> pages;

public:

    ReplacementAlgorithm();
    ReplacementAlgorithm(std::size_t _RAMFrames);
    
    virtual ~ReplacementAlgorithm();

    std::vector<Page> getPages() const;

    virtual int accessMemory(std::size_t page) = 0;

};


class FIFOAlgorithm : public ReplacementAlgorithm {

public:

    FIFOAlgorithm();
    FIFOAlgorithm(std::size_t _RAMFrames);

    ~FIFOAlgorithm();

    int accessMemory(std::size_t page);

};


class LRUAlgorithm : public ReplacementAlgorithm {

public:

    LRUAlgorithm();
    LRUAlgorithm(std::size_t _RAMFrames);

    ~LRUAlgorithm();

    int accessMemory(std::size_t page);

};

#endif