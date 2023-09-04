#ifndef _H_SCHEDULER
#define _H_SCHEDULER

#include <vector>

#include "scheduling_algorithm.h"
#include "process.h"
#include "cpu.h"

class Scheduler {

    private:

    SchedulingAlgorithm *algorithm;

    public:

    Scheduler() {};
    ~Scheduler() {};

    int isItTimeToSwitch(CPU *cpu, std::vector<Process *> processes) {
        return algorithm->isItTimeToSwitch(cpu, processes);
    }

    Process *getNextProcess(std::vector<Process *> &processes) {
        std::vector<Process *> ps = algorithm->schedule(processes);
        // TODO arrumar o auto
        auto itP = ps.begin();
        Process *p = *itP;
        processes.erase(itP);
        return p;
    }

};

#endif