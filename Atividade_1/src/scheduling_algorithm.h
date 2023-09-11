#ifndef _H_SCHEDULING_ALGORITHMS
#define _H_SCHEDULING_ALGORITHMS


#include <algorithm>
#include <vector>

#include "process.h"
#include "cpu.h"


class SchedulingAlgorithm {

public:
    
    // TODO ver sobre construtores e destrutores de classe abstrata
    SchedulingAlgorithm();
    
    virtual ~SchedulingAlgorithm();
    
    virtual int isItTimeToSwitch(CPU *cpu, std::vector<Process *> processes);

    virtual std::vector<Process *> &schedule(std::vector<Process *> &processes) = 0;
};

class FCFS : public SchedulingAlgorithm {

public:

    FCFS() {}
    ~FCFS() {}

    std::vector<Process *> &schedule(std::vector<Process *> &processes) override;
};

class SJF: public SchedulingAlgorithm {

public:

    std::vector<Process *> &schedule(std::vector<Process *> &processes) override;
};

class Priority: public SchedulingAlgorithm {

public:

    std::vector<Process *> &schedule(std::vector<Process *> &processes) override;
};

class PriorityWithPreemption : public SchedulingAlgorithm {

public:

    std::vector<Process *> &schedule(std::vector<Process *> &processes) override;

    int isItTimeToSwitch(CPU *cpu, std::vector<Process *> processes) override;
};

class RoundRobin : public SchedulingAlgorithm {

public:

    std::vector<Process *> &schedule(std::vector<Process *> &processes) override;

    int isItTimeToSwitch(CPU *cpu, std::vector<Process *> processes) override;
};

#endif