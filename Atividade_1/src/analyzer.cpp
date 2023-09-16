
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

#include "analyzer.h"
#include "process.h"
#include "kernel.h"
#include "utils.h"

//Classe responsável por analisar as métricas de cada algoritmo de escalonamento
void Analyzer::analyze(Kernel *kernel) {
    std::vector<std::vector<State>> executionHistory = kernel->getExecutionHistory();
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
    customCout("DIAGRAMA DE TEMPO\n\n", BRIGHT_RED);
    int width = std::log10(pcb.size()) + 1;
    setColor(BRIGHT_WHITE);
    std::cout << "tempo ";
    for (auto p : pcb) std::cout << "P" << std::setw(width) << std::setfill('0') << p->getId() << " ";
    std::cout << std::setfill(' ') << std::endl;
    resetColor();
    
    // No output gerado para os processos a cor vermelha representa que
    // o processo foi iniciado e está pronto para ser executado
    // a cor verde representa que o processo está sendo executado
    for (long unsigned int i = 0; i < executionHistory.size(); i++) {
        std::string interval = std::to_string(i) + "-" + std::to_string(i + 1);
        setColor(BRIGHT_WHITE);
        std::cout << std::setw(5) << interval << " ";
        resetColor();

        int width = std::log10(executionHistory[i].size()) + 1;
        for (auto state : executionHistory[i]) {
            if (state == EXECUTANDO) {customCout("  ", WEAK_GREEN_BACKGROUND); std::cout << std::setw(width) << " ";}
            else if (state == NOVO) std::cout << std::setw(width + 2) << " ";
            else if (state == PRONTO) {customCout("  ", WEAK_RED_BACKGROUND);  std::cout << std::setw(width) << " ";}
            else std::cout << std::setw(width + 2) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;

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