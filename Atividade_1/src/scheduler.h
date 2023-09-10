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

    Scheduler(SchedulingAlgorithm *_algorithm);
    ~Scheduler();

    SchedulingAlgorithm *getAlgorithm() const;
    void setAlgorithm(SchedulingAlgorithm *_algorithm);

    int isItTimeToSwitch(CPU *cpu, std::vector<Process *> processes);

    Process *getNextProcess(std::vector<Process *> &processes);

};

#endif