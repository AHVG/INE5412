#include "kernel.h"
#include <iostream>

int main() {

    std::cout << "Simulador de algoritmos de escalonamento" << std::endl;

    Kernel kernel;
    kernel.initialize();
    kernel.run();
    kernel.close();

    return 0;
}
