
#include "replacementAlgorithm.h"

#include <algorithm>


ReplacementAlgorithm::ReplacementAlgorithm() : RAMFrames(0) {}


ReplacementAlgorithm::ReplacementAlgorithm(std::size_t _RAMFrames) : RAMFrames(_RAMFrames) {}


ReplacementAlgorithm::~ReplacementAlgorithm() {}


std::vector<Page> ReplacementAlgorithm::getPages() const {
    return pages;
}


FIFOAlgorithm::FIFOAlgorithm() : ReplacementAlgorithm() {}


FIFOAlgorithm::FIFOAlgorithm(std::size_t _RAMFrames) : ReplacementAlgorithm(_RAMFrames) {}


FIFOAlgorithm::~FIFOAlgorithm() {}


int FIFOAlgorithm::accessMemory(std::size_t page) {

    auto it = std::find_if(pages.begin(), pages.end(), [page] (const Page &p) {
        return p.getId() == page;
    });

    if (it == pages.end()) {
        Page aux(page, 0);
        pages.push_back(aux);
        if (pages.size() > RAMFrames) {
            pages.erase(pages.begin());
        }
        return 0;
    }

    return 1;
}


LRUAlgorithm::LRUAlgorithm(std::size_t _RAMFrames) : ReplacementAlgorithm(_RAMFrames) {}


LRUAlgorithm::~LRUAlgorithm() {}


int LRUAlgorithm::accessMemory(std::size_t page) {

    auto it = std::find_if(pages.begin(), pages.end(), [page] (const Page &p) {
        return p.getId() == page;
    });

    if (it == pages.end()) {
        Page aux(page, 0);
        pages.push_back(aux);
        if (pages.size() > RAMFrames) {
            pages.erase(pages.begin());
        }
        return 0;
    }
    
    Page aux(*it);
    pages.erase(it);
    pages.push_back(aux);

    return 1;
}
