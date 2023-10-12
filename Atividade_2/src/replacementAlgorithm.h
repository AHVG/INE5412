#ifndef _H_ALGORITHM
#define _H_ALGORITHM

#include <iostream>
#include <vector>


class ReplacementAlgorithm {

protected:

    std::size_t RAMFrames;
    std::vector<std::size_t> pages;

public:

    ReplacementAlgorithm();
    ReplacementAlgorithm(std::size_t _RAMFrames);
    
    virtual ~ReplacementAlgorithm();

    std::vector<std::size_t> getPages() const;

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
private:
    std::size_t entrySize;
    std::vector<std::size_t> lines;
    int currentLine;
public:
    OPTAlgorithm();
    OPTAlgorithm(std::size_t _RAMFrames, std::vector<std::size_t> lines);

    ~OPTAlgorithm();

    int accessMemory(std::size_t page);
    std::size_t findNextOcurrence(std::size_t index, std::size_t id);
};

#endif