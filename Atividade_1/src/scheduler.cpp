
#include <vector>

#include "scheduling_algorithm.h"
#include "scheduler.h"
#include "process.h"
#include "kernel.h"
#include "cpu.h"


Scheduler::Scheduler(SchedulingAlgorithm *_algorithm) {
    algorithm = _algorithm;
}

Scheduler::~Scheduler() {}

SchedulingAlgorithm *Scheduler::getAlgorithm() const {
    return algorithm;
}

void Scheduler::setAlgorithm(SchedulingAlgorithm *_algorithm) {
    algorithm = _algorithm;
}

int Scheduler::isItTimeToSwitch(CPU *cpu, std::vector<Process *> processes) {
    return algorithm->isItTimeToSwitch(cpu, processes);
}

Process *Scheduler::getNextProcess(std::vector<Process *> &processes) {
    if (processes.empty()) return nullptr;
    algorithm->schedule(processes);
    // TODO arrumar o auto
    auto itP = processes.begin();
    Process *p = *itP;
    processes.erase(itP);
    return p;
}
