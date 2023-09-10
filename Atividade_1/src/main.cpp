
#include <iostream>
#include <vector>

#include "kernel.h"
#include "scheduling_algorithm.h"


int main() {

    std::cout << "Simulador de algoritmos de escalonamento\n\n";

    std::vector<SchedulingAlgorithm *> algorithms = {new QuantumWithoutPriority(), new FCFS(), new PriorityWithPreemption(), new SJF(), new Priority()};
    for (auto algorithm : algorithms) {
        Kernel *kernel = new Kernel(algorithm);
        kernel->run();
        delete kernel;
    }
    for (long unsigned int i = 0; i < algorithms.size(); i++) delete algorithms[i];

    return 0;
}
