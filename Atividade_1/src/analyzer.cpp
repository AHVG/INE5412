
#include <iostream>
#include <iomanip>
#include <vector>

#include "analyzer.h"
#include "process.h"
#include "kernel.h"
#include "utils.h"


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

    // Calculando o tempo de espera de cada processo
    std::vector<int> waitingTimePerProcess(pcb.size());
    std::transform(pcb.begin(), pcb.end(), waitingTimePerProcess.begin(), [](Process *p) {
        return p->getEnd() - p->getStart() - p->getDuration();
    });

    // Calculando o tempo médio de espera dos processo
    double averageWaitingTime = 0;
    for (auto t : waitingTimePerProcess) averageWaitingTime += t;
    averageWaitingTime /= waitingTimePerProcess.size();

    // Número de trocas de contexto
    double contextSwitches = kernel->getContextSwitches();

    // Mostrando as estatísticas
    customCout("METRICAS\n\n", BRIGHT_RED);
    std::cout << GREEN << "      Tempo de resposta por processo: " << WHITE;
    for (long unsigned int i = 0; i < turnaroundTimePerProcess.size(); i++) 
        std::cout << "P" << i + 1 << " - " << turnaroundTimePerProcess[i] << " ciclos ";
    std::cout << RESET_COLOR << std::endl;
    std::cout << GREEN << "      Tempo médio de resposta:        " << WHITE << averageTurnaroundTime << " ciclos" << std::endl;
    std::cout << GREEN << "      Tempo médio de espera:          " << WHITE << averageWaitingTime << " ciclos" << std::endl;
    std::cout << GREEN << "      Número de trocas de contexto:   " << WHITE << contextSwitches << " trocas" << std::endl;
    std::cout << std::endl;

}