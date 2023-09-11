
#include <iostream>
#include <vector>

#include "kernel.h"
#include "scheduling_algorithm.h"


int main() {

    std::cout << "\033[1;31mSimulador de algoritmos de escalonamento\033[0m\n\n";

    std::vector<SchedulingAlgorithm *> algorithms = {new QuantumWithoutPriority(), new FCFS(), new PriorityWithPreemption(), new SJF(), new Priority()};
    for (auto algorithm : algorithms) {
        Kernel kernel(algorithm);
        kernel.run();
    }
    for (long unsigned int i = 0; i < algorithms.size(); i++) delete algorithms[i];

    return 0;
}
