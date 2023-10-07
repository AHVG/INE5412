
#include "algorithm.h"

Algorithm::Algorithm() : RAMFrames(0) {}


Algorithm::Algorithm(std::size_t _RAMFrames) : RAMFrames(_RAMFrames) {}


Algorithm::~Algorithm() {}


FifoAlgorithm::FifoAlgorithm() : Algorithm() {}


FifoAlgorithm::FifoAlgorithm(std::size_t _RAMFrames) : Algorithm(_RAMFrames) {}


FifoAlgorithm::~FifoAlgorithm() {}


int FifoAlgorithm::accessMemory(std::size_t page) {

}
