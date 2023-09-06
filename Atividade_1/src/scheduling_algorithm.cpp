
#include <algorithm>
#include <vector>

#include "scheduling_algorithm.h"
#include "process.h"
#include "cpu.h"


SchedulingAlgorithm::SchedulingAlgorithm() {}

SchedulingAlgorithm::~SchedulingAlgorithm() {}
    
int SchedulingAlgorithm::isItTimeToSwitch(CPU *cpu, std::vector<Process *> processes) {
    if (processes.empty()) return 0;
    if (cpu->empty() || cpu->finishExecuting()) return 1;
    return 0;
}

std::vector<Process *> FCFS::schedule(std::vector<Process *> processes) {
    return processes;
}

std::vector<Process *> SJF::schedule(std::vector<Process *> processes) {
    std::sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.getDuration() < b.getDuration();
    });
    return processes;
}

std::vector<Process *> Priority::schedule(std::vector<Process *> processes) {
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.getPriority() > b.getPriority();
    });
    return processes;
}

std::vector<Process *> PriorityWithPreemption::schedule(std::vector<Process *> processes) {
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.getPriority() > b.getPriority();
    });
    return processes;
}

int PriorityWithPreemption::isItTimeToSwitch(CPU *cpu, std::vector<Process *> processes) {
    Process *currentProcess = cpu->getProcess();
    if (std::any_of(processes.begin(), processes.end(), [currentProcess](Process *p) {return p->getPriority() > currentProcess->getPriority();})) return 1;
    return SchedulingAlgorithm::isItTimeToSwitch(cpu, processes);
}
