#ifndef _H_SCHEDULING_ALGORITHMS
#define _H_SCHEDULING_ALGORITHMS


#include <algorithm>
#include <vector>

#include "process.h"
#include "cpu.h"


class SchedulingAlgorithm {

public:
    
    // TODO ver sobre construtores e destrutores de classe abstrata
    SchedulingAlgorithm() {};
    
    ~SchedulingAlgorithm() {};
    
    virtual int isItTimeToSwitch(CPU *cpu, std::vector<Process *> processes) {
        if (processes.empty()) return 0;
        if (cpu->empty() || cpu->finishExecuting()) return 1;
        return 0;
    };

    virtual std::vector<Process *> schedule(std::vector<Process *> processes) = 0;
};

class FCFS: public SchedulingAlgorithm {

public:

    std::vector<Process *> schedule(std::vector<Process *> processes) override {
        return processes;
    };
};

class SJF: public SchedulingAlgorithm {

public:

    std::vector<Process *> schedule(std::vector<Process *> processes) override {
        std::sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
            return a.getDuration() < b.getDuration();
        });
        return processes;
    };
};

class Priority: public SchedulingAlgorithm {

public:

    std::vector<Process *> schedule(std::vector<Process *> processes) override{
        std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
            return a.getPriority() > b.getPriority();
        });
        return processes;
    };
};

class PriorityWithPreemption : public SchedulingAlgorithm {

public:

    std::vector<Process *> schedule(std::vector<Process *> processes) override{
        std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
            return a.getPriority() > b.getPriority();
        });
        return processes;
    };

    int isItTimeToSwitch(CPU *cpu, std::vector<Process *> processes) {
        Process *currentProcess = cpu->getProcess();
        if (std::any_of(processes.begin(), processes.end(), [currentProcess](Process *p) {return p->getPriority() > currentProcess->getPriority();})) return 1;
        return SchedulingAlgorithm::isItTimeToSwitch(cpu, processes);
    };
}

#endif