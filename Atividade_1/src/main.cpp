
#include <iostream>
#include <vector>

#include "scheduling_algorithm.h"
#include "kernel.h"
#include "utils.h"


int main() {

    customCout("SIMULADOR DE ALGORITMO DE ESCALONAMENTO\n\n", BRIGHT_CYAN);
    while(1){
        customCout("INSIRA O NOME DO ALGORITMO DE ESCALONAMENTO QUE DESEJA SIMULAR\n", BRIGHT_CYAN);
        customCout("OPCOES: 1 -> FCFS, 2 -> SJF, 3 -> PRIORITY, 4 -> PRIORITY WITH PREEMPTION,  5-> ROUND ROBIN, 6 -> SAIR\n", BRIGHT_CYAN);
        int option;
        std::cin >> option;
        std::cout << std::endl;
        if (option == 1){
            customCout("SIMULANDO FCFS\n\n", BRIGHT_YELLOW);
            Kernel kernel(new FCFS());
            kernel.run();
            customCout("FIM DA SIMULACAO\n\n", BRIGHT_YELLOW);
        }
        else if (option == 2){
            customCout("SIMULANDO SJF\n\n", BRIGHT_YELLOW);
            Kernel kernel(new SJF());
            kernel.run();
            customCout("FIM DA SIMULACAO\n\n", BRIGHT_YELLOW);
        }
        else if (option == 3){
            customCout("SIMULANDO PRIORITY\n\n", BRIGHT_YELLOW);
            Kernel kernel(new Priority());
            kernel.run();
            customCout("FIM DA SIMULACAO\n\n", BRIGHT_YELLOW);
        }
        else if (option == 4){
            customCout("SIMULANDO PRIORITY WITH PREEMPTION\n\n", BRIGHT_YELLOW);
            Kernel kernel(new PriorityWithPreemption());
            kernel.run();
            customCout("FIM DA SIMULACAO\n\n", BRIGHT_YELLOW);
        }
        else if (option == 5){
            customCout("SIMULANDO ROUND ROBIN\n\n", BRIGHT_YELLOW);
            Kernel kernel(new RoundRobin());
            kernel.run();
            customCout("FIM DA SIMULACAO\n\n", BRIGHT_YELLOW);
        }
        else if (option == 6){
            break;
        }
        else{
            customCout("OPCAO INVALIDA\n\n", BRIGHT_RED);
        }
    }

    customCout("FIM DAS SIMULACOES\n\n", BRIGHT_CYAN);

    return 0;
}
