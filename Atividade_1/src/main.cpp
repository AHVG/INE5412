
#include <iostream>
#include <vector>

#include "scheduling_algorithm.h"
#include "kernel.h"
#include "utils.h"


int main() {

    customCout("SIMULADOR DE ALGORITMO DE ESCALONAMENTO\n\n", BRIGHT_CYAN);

    std::vector<std::pair<std::string, SchedulingAlgorithm *>> algorithms = { {"FCFS", new FCFS()},
                                                                {"SJF", new SJF()},
                                                                {"PRIORITY", new Priority()},
                                                                {"PRIORITY WITH PREEMPTION", new PriorityWithPreemption()},
                                                                {"ROUND ROBIN", new RoundRobin()}};
    for (auto algorithm : algorithms) {
        customCout("SIMULANDO " + algorithm.first + "\n\n", BRIGHT_YELLOW);
        Kernel kernel(algorithm.second);
        kernel.run();
        // Será que é viavel fazer a análise do kernel após ele executar, colocando o analyzer aqui?
        customCout("FIM DA SIMULACAO\n\n", BRIGHT_YELLOW);
    }
    for (auto &algorithm : algorithms) delete algorithm.second;

    customCout("FIM DAS SIMULACOES\n\n", BRIGHT_CYAN);

    return 0;
}
