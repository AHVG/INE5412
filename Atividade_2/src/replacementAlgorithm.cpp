
#include "replacementAlgorithm.h"

#include <algorithm>


ReplacementAlgorithm::ReplacementAlgorithm() : RAMFrames(0) {}


ReplacementAlgorithm::ReplacementAlgorithm(std::size_t _RAMFrames) : RAMFrames(_RAMFrames) {}


ReplacementAlgorithm::~ReplacementAlgorithm() {}


FifoAlgorithm::FifoAlgorithm() : ReplacementAlgorithm() {}


FifoAlgorithm::FifoAlgorithm(std::size_t _RAMFrames) : ReplacementAlgorithm(_RAMFrames) {}


FifoAlgorithm::~FifoAlgorithm() {}


int FifoAlgorithm::accessMemory(std::size_t page) {
    auto it = std::find_if(pages.begin(), pages.end(), [page] (const Page &p) {
        return p.getId() == page;
    });

    int misses = 0;
    
    if (it != pages.end()) {
        std::cout << "Hit" << std::endl;
    } else {
        std::cout << "Miss" << std::endl;
        Page aux(page, 0);
        pages.push_back(aux);
        if (pages.size() > RAMFrames) {
            pages.erase(pages.begin());
        }
        misses = 1;
    }

    for (auto p : pages) {
        std::cout << p << ", ";
    }

    std::cout << "\n";

    return misses;
}
