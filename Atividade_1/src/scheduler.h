#ifndef _H_SCHEDULER
#define _H_SCHEDULER

#include "scheduling_algorithm.h"
#include "cpu.h"

class Scheduler {

    private:

    SchedulingAlgorithm *algorithm;

    public:

    Scheduler() {};
    ~Scheduler() {};

    Process *getNextProcess() {
        return nullptr;
    }

};

#endif