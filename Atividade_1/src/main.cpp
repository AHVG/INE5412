
#include <iostream>
#include <vector>

#include "scheduling_algorithm.h"
#include "kernel.h"
#include "utils.h"


int main() {

    customCout("SIMULADOR DE ALGORITMO DE ESCALONAMENTO\n\n", BRIGHT_CYAN);
    std::vector<std::pair<std::string, SchedulingAlgorithm *>> algorithms = {
                {"FCFS", new FCFS()},
                {"SJF", new SJF()},
                {"PRIORITY", new Priority()},
                {"PRIORITY WITH PREEMPTION", new PriorityWithPreemption()},
                {"ROUND ROBIN", new RoundRobin()}};
    while(1){
        customCout("INSIRA O NOME DO ALGORITMO DE ESCALONAMENTO QUE DESEJA SIMULAR\n", BRIGHT_CYAN);
        customCout("OPCOES: 1 -> FCFS, 2 -> SJF, 3 -> PRIORITY, 4 -> PRIORITY WITH PREEMPTION,  5 -> ROUND ROBIN, 6 -> RODAR TODOS, 7 -> SAIR\n", BRIGHT_CYAN);
        
        int option;
        int startInterval = 0;
        std::cin >> option;
        std::cout << std::endl;

        if (option == 7) break;
        if (option < 0 || 6 < option){ customCout("OPCAO INVALIDA\n\n", BRIGHT_RED); continue;}

        if (option == 6) {startInterval = 0; option = 5;}
        else startInterval = option - 1;
        
        for (int i = startInterval; i < option; i++) {
            customCout("SIMULANDO " + algorithms[i].first + "\n\n", BRIGHT_YELLOW);
            Kernel kernel(algorithms[i].second);
            kernel.run();
            customCout("FIM DA SIMULACAO\n\n", BRIGHT_YELLOW);
        }
    }

    for (auto &algorithm : algorithms) delete algorithm.second;

    customCout("FIM DAS SIMULACOES\n\n", BRIGHT_CYAN);

    return 0;
}
