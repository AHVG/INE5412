
#include <iostream>
#include <vector>

#include "analyzer.h"
#include "kernel.h"
#include "process.h"


void Analyzer::analyze(Kernel *kernel) {
    std::vector<Process *> pcb = kernel->getPCB();
    
    // Calculando o tempo transcorrido de cada processo
    std::vector<int> turnaroundTimePerProcess(pcb.size());
    std::transform(pcb.begin(), pcb.end(), turnaroundTimePerProcess.begin(), [](Process *p) {
        return p->getEnd() - p->getStart();
    });
    
    // Calculando tempo médio transcorrido dos processos
    double averageTurnaroundTime = 0;
    for (auto t : turnaroundTimePerProcess) averageTurnaroundTime += t;
    averageTurnaroundTime /= turnaroundTimePerProcess.size();

    // Calculando o tempo médio de espera dos processo
    double averageWaitingTime = 0;

    // Número de trocas de contexto
    double contextSwitches = kernel->getContextSwitches();

    // Mostrando as estatísticas
    std::cout << averageTurnaroundTime << std::endl;
    std::cout << averageWaitingTime << std::endl;
    std::cout << contextSwitches << std::endl;

}