#include "kernel.h"
#include <iostream>

int main() {

  stc::cout << "Simulador de algoritmos de escalonamento" << std::endl;

  Kernel kernel;
  kernel.run();
  kernel.close();

  return 0;
}
