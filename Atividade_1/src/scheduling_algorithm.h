#ifndef _H_SCHEDULING_ALGORITHMS
#define _H_SCHEDULING_ALGORITHMS



#include <vector>
#include "process.h"
#include <algorithm>

class SchedulingAlgorithm {

public:
    
    SchedulingAlgorithm() {};
    
    ~SchedulingAlgorithm() {};
    
    std::vector<Process *> schedule(std::vector<Process *> processes) virtual=0;

    std::vector<Process *> FCFS(std::vector<Process *> processes){
        return processes;
    }

    std::vector<Process *> SJF(std::vector<Process *> processes){
        std::sort(processes.begin(), processes.end(), compareByDuration);
        return processes;
    }

    std::vector<Process *> priority(std::vector<Process *> processes){
        std::sort(processes.begin(), processes.end(), compareByPriority);
        return processes;
    }
    
private:

    bool compareByDuration(const Process& a, const Process& b) {
        return a.getDuration() < b.getDuration();
    }

    bool compareByPriority(const Process& a, const Process& b) {
        return a.getPriority() > b.getPriority();
    }
};

#endif