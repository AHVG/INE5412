#include <vector>
#include "process.h"
#include "algorithm"
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

bool compareByDuration(const Process& a, const Process& b) {
    return a.getDuration() < b.getDuration();
}

bool compareByPriority(const Process& a, const Process& b) {
    return a.getPriority() > b.getPriority();
}