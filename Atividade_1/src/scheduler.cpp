
#include <vector>

#include "scheduler.h"
#include "process.h"
#include "cpu.h"


Scheduler::Scheduler() {}
Scheduler::~Scheduler() {}

int Scheduler::isItTimeToSwitch(CPU *cpu, std::vector<Process *> processes) {
    return algorithm->isItTimeToSwitch(cpu, processes);
}

Process *Scheduler::getNextProcess(std::vector<Process *> &processes) {
    std::vector<Process *> ps = algorithm->schedule(processes);
    // TODO arrumar o auto
    auto itP = ps.begin();
    Process *p = *itP;
    processes.erase(itP);
    return p;
}
