#ifndef _H_SCHEDULING_ALGORITHMS
#define _H_SCHEDULING_ALGORITHMS



#include <vector>
#include "process.h"
#include <algorithm>

class SchedulingAlgorithm {

private:

public:
    
    SchedulingAlgorithm() {};
    
    ~SchedulingAlgorithm() {};
    
    virtual std::vector<Process *> schedule(std::vector<Process *> processes) = 0;
};

class FCFS: public SchedulingAlgorithm {

private:

public:

    std::vector<Process *> schedule(std::vector<Process *> processes) override {
        return processes;
    };
};

class SJF: public SchedulingAlgorithm {

private:

public:

    std::vector<Process *> schedule(std::vector<Process *> processes) override {
        std::sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
            return a.getDuration() < b.getDuration();
        });
        return processes;
    }
};

class Priority: public SchedulingAlgorithm {

private:

public:

    std::vector<Process *> schedule(std::vector<Process *> processes) override{
        std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
            return a.getPriority() > b.getPriority();
        });
        return processes;
    };
};

#endif