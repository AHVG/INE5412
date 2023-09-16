
#include <vector>

#include "scheduling_algorithm.h"
#include "scheduler.h"
#include "process.h"
#include "kernel.h"
#include "cpu.h"

// Classe responsável por gerenciar o escalonamento dos processos
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

// Verifica se é hora de trocar de processo
int Scheduler::isItTimeToSwitch(CPU *cpu, std::vector<Process *> processes) {
    return algorithm->isItTimeToSwitch(cpu, processes);
}

// Pega o próximo processo a ser executado
Process *Scheduler::getNextProcess(std::vector<Process *> &processes) {
    if (processes.empty()) return nullptr;
    algorithm->schedule(processes);
    return processes[0];
}
