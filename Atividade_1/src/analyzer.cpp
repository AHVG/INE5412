
#include <iostream>
#include <iomanip>
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
    std::cout << "METRICAS\n\n";
    std::cout << "      Tempo de resposta por processo:    ";
    for (long unsigned int i = 0; i < turnaroundTimePerProcess.size(); i++) 
        std::cout << "P" << i + 1 << " - " << turnaroundTimePerProcess[i] << " ciclos ";
    std::cout << std::endl;
    std::cout << "      Tempo médio de resposta:           " << averageTurnaroundTime << " ciclos" << std::endl;
    std::cout << "      Tempo médio de espera:             " << averageWaitingTime << " ciclos" << std::endl;
    std::cout << "      Número de trocas de contexto:      " << contextSwitches << " trocas" << std::endl;

    std::cout << "\nFIM\n\n";

}