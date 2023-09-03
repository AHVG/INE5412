#include "kernel.h"
#include <iostream>

int main() {

    std::cout << "Simulador de algoritmos de escalonamento\n\n";

    Kernel kernel;
    kernel.initialize();
    kernel.run();
    kernel.close();

    return 0;
}
