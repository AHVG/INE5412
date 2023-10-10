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

    int full();

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

class OPTAlgorithm : public ReplacementAlgorithm {

public:
    OPTAlgorithm();
    OPTAlgorithm(std::size_t _RAMFrames);

    ~OPTAlgorithm();

    int accessMemory(std::size_t page);
    void refreshTags(std::vector<std::size_t> lines, std::size_t index);
    std::size_t findNextOcurrence(std::vector<std::size_t> lines, std::size_t index, std::size_t id);
    std::size_t getPageWithMaxTag();
    int in(std::size_t id);
};

#endif