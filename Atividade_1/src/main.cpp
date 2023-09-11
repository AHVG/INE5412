
#include <iostream>
#include <vector>
#include <map>

#include "scheduling_algorithm.h"
#include "kernel.h"
#include "utils.h"


int main() {

    customCout("SIMULADOR DE ALGORITMO DE ESCALONAMENTO\n\n", BRIGHT_CYAN);

    std::map<std::string, SchedulingAlgorithm *> algorithms = { {"FCFS", new FCFS()},
                                                                {"SJF", new SJF()},
                                                                {"PRIORITY", new Priority()},
                                                                {"PRIORITY WITH PREEMPTION", new PriorityWithPreemption()},
                                                                {"QUANTUM", new QuantumWithoutPriority()}};
    for (auto algorithm : algorithms) {
        customCout("SIMULANDO " + algorithm.first + "\n\n", BRIGHT_YELLOW);
        Kernel kernel(algorithm.second);
        kernel.run();
        customCout("FIM DA SIMULACAO\n\n", BRIGHT_YELLOW);
    }
    for (auto &algorithm : algorithms) delete algorithm.second;

    customCout("FIM DAS SIMULACOES\n\n", BRIGHT_CYAN);

    return 0;
}
