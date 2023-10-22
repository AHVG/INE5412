#ifndef _H_ALGORITHM
#define _H_ALGORITHM

#include <iostream>
#include <vector>


class ReplacementAlgorithm {

protected:

    std::size_t RAMFrames;
    std::vector<std::size_t> pages;
    std::vector<std::size_t> &lines;

public:

    ReplacementAlgorithm(std::size_t _RAMFrames, std::vector<std::size_t> &_lines);
    
    virtual ~ReplacementAlgorithm();

    virtual std::size_t simulate() = 0;

    std::vector<std::size_t>::iterator containsPage(std::size_t page);

};


class FIFOAlgorithm : public ReplacementAlgorithm {

public:

    FIFOAlgorithm(std::size_t _RAMFrames, std::vector<std::size_t> &lines);

    ~FIFOAlgorithm();

    std::size_t simulate();

};


class LRUAlgorithm : public ReplacementAlgorithm {

public:

    LRUAlgorithm(std::size_t _RAMFrames, std::vector<std::size_t> &lines);

    ~LRUAlgorithm();

    std::size_t simulate();

};


class OPTAlgorithm : public ReplacementAlgorithm {

private:

    std::size_t entrySize;
    
    int currentLine;

public:
    OPTAlgorithm(std::size_t _RAMFrames, std::vector<std::size_t> &lines);

    ~OPTAlgorithm();

    std::size_t simulate();
    std::size_t findNextOcurrence(std::size_t index, std::size_t id);
};

#endif