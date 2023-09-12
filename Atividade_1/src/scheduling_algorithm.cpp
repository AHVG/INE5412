
#include <algorithm>
#include <vector>

#include "scheduling_algorithm.h"
#include "process.h"
#include "cpu.h"

// Classe abstrata que contera todos os algoritmos de escalonamento
SchedulingAlgorithm::SchedulingAlgorithm(){}

SchedulingAlgorithm::~SchedulingAlgorithm(){}

// Verifica se é hora de trocar de processo    
int SchedulingAlgorithm::isItTimeToSwitch(CPU *cpu, std::vector<Process *> processes) {
    if (!processes.empty() && cpu->empty()) return 1;
    if (cpu->getProcess() && cpu->getProcess()->finished()) return 1;

    return 0;
}

std::vector<Process *> &FCFS::schedule(std::vector<Process *> &processes) {
    return processes;
}
// Ordena os processos pelo tempo de duração
std::vector<Process *> &SJF::schedule(std::vector<Process *> &processes) {
    std::sort(processes.begin(), processes.end(), [](const Process *a, const Process *b) {
        return a->getDuration() < b->getDuration();
    });
    return processes;
}
// Ordena os processos pela prioridade
std::vector<Process *> &Priority::schedule(std::vector<Process *> &processes) {
    std::sort(processes.begin(), processes.end(), [](const Process *a, const Process *b) {
        return a->getPriority() > b->getPriority();
    });
    return processes;
}
std::vector<Process *> &PriorityWithPreemption::schedule(std::vector<Process *> &processes) {
    std::sort(processes.begin(), processes.end(), [](const Process *a, const Process *b) {
        return a->getPriority() > b->getPriority();
    });
    return processes;
}
// Verifica se é hora de trocar de processo para que assim a preempção ocorra
int PriorityWithPreemption::isItTimeToSwitch(CPU *cpu, std::vector<Process *> processes) {
    Process *currentProcess = cpu->getProcess();
    if (currentProcess)
        if (std::any_of(processes.begin(), processes.end(), [currentProcess](Process *p) {
            return p->getPriority() > currentProcess->getPriority();
        })) return 1;
    return SchedulingAlgorithm::isItTimeToSwitch(cpu, processes);
}

std::vector<Process *> &RoundRobin::schedule(std::vector<Process *> &processes){
    return processes;
}
// Verifica se é hora de trocar de processo, vendo se o processo atual ja chegou no seu tempo limite(quantum)
// Nesse caso o quantum é 2 
int RoundRobin::isItTimeToSwitch(CPU *cpu, std::vector<Process *> processes) {
    if(cpu->getTimeRunningCurrentProcess() == cpu->getQuantum()) return 1;
    return SchedulingAlgorithm::isItTimeToSwitch(cpu, processes);
}