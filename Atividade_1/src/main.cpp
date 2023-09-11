
#include <iostream>
#include <vector>
#include <map>

#include "scheduling_algorithm.h"
#include "kernel.h"
#include "utils.h"


int main() {

    std::cout << "\033[1;31mSimulador de algoritmos de escalonamento\033[0m\n\n";

    std::map<std::string, SchedulingAlgorithm *> algorithms = { {"FCFS", new FCFS()},
                                                                {"SJF", new SJF()},
                                                                {"PRIORITY", new Priority()},
                                                                {"PRIORITY WITH PREEMPTION", new PriorityWithPreemption()},
                                                                {"QUANTUM", new QuantumWithoutPriority()}};
    for (auto algorithm : algorithms) {
        customCout("SIMULANDO " + algorithm.first + "\n\n", BRIGHT_YELLOW);
        Kernel kernel(algorithm.second);
        kernel.run();
        customCout("FIM DA SIMULACAO DO " + algorithm.first + "\n\n", BRIGHT_YELLOW);
    }
    for (auto &algorithm : algorithms) delete algorithm.second;

    customCout("P", BLACK);
    customCout("A", RED);
    customCout("L", GREEN);
    customCout("E", YELLOW);
    customCout("T", BLUE);
    customCout("A", MAGENTA);
    customCout(" ", CYAN);
    customCout("D", CYAN);
    customCout("E", WHITE);
    customCout(" ", BRIGHT_BLACK);
    customCout("C", BRIGHT_BLACK);
    customCout("O", BRIGHT_RED);
    customCout("R\n", BRIGHT_GREEN);
    customCout("Texto em Preto\n", BLACK);
    customCout("Texto em Vermelho\n", RED);
    customCout("Texto em Verde\n", GREEN);
    customCout("Texto em Amarelo\n", YELLOW);
    customCout("Texto em Azul\n", BLUE);
    customCout("Texto em Magenta\n", MAGENTA);
    customCout("Texto em Ciano\n", CYAN);
    customCout("Texto em Branco\n", WHITE);
    customCout("Texto em Preto Brilhante\n", BRIGHT_BLACK);
    customCout("Texto em Vermelho Brilhante\n", BRIGHT_RED);
    customCout("Texto em Verde Brilhante\n", BRIGHT_GREEN);
    customCout("Texto em Amarelo Brilhante\n", BRIGHT_YELLOW);
    customCout("Texto em Azul Brilhante\n", BRIGHT_BLUE);
    customCout("Texto em Magenta Brilhante\n", BRIGHT_MAGENTA);
    customCout("Texto em Ciano Brilhante\n", BRIGHT_CYAN);
    customCout("Texto em Branco Brilhante\n", BRIGHT_WHITE);

    return 0;
}
