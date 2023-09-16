#ifndef _H_SIMULATOR
#define _H_SIMULATOR

#include <vector>
#include <string>

#include "scheduling_algorithm.h"


class Simulator {

    std::vector<std::pair<std::string, SchedulingAlgorithm *>> algorithms;

    void runAnAlgorithm(long unsigned int index);

public:

    Simulator();
    ~Simulator();

    void run();

};

#endif