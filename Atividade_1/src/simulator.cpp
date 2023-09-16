
#include <iostream>
#include <vector>

#include "simulator.h"
#include "scheduling_algorithm.h"
#include "analyzer.h"
#include "kernel.h"
#include "utils.h"


Simulator::Simulator() : algorithms({{"FCFS", new FCFS()},
                                    {"SJF", new SJF()},
                                    {"PRIORITY", new Priority()},
                                    {"PRIORITY WITH PREEMPTION", new PriorityWithPreemption()},
                                    {"ROUND ROBIN", new RoundRobin()}}) {
}
Simulator::~Simulator() {
    for (auto &algorithm : algorithms) delete algorithm.second;
    algorithms.clear();
}

void Simulator::run() {
    customCout("SIMULADOR DE ALGORITMO DE ESCALONAMENTO\n\n", BRIGHT_CYAN);
    for(;;) {

        customCout("INSIRA O NOME DO ALGORITMO DE ESCALONAMENTO QUE DESEJA SIMULAR\n", BRIGHT_CYAN);
        customCout("\n 0 -> FCFS\n 1 -> SJF\n 2 -> PRIORITY\n 3 -> PRIORITY WITH PREEMPTION\n 4 -> ROUND ROBIN\n 5 -> RODAR TODOS\n-1 -> SAIR\n", BRIGHT_CYAN);
        
        int option;
        std::cout << "> ";
        std::cin >> option;
        std::cout << std::endl;

        if (option == -1) break; // Usuário quer sair
        if (option < 0 || 5 < option) {customCout("OPCAO INVALIDA\n\n", BRIGHT_RED); continue;} // Opção não existe, tenta novamente

        if (option == 5) for (int i = 0; i < 5; i++) runAnAlgorithm(i);
        else runAnAlgorithm(option);
    }

    customCout("FIM DAS SIMULACOES\n\n", BRIGHT_CYAN);

}

void Simulator::runAnAlgorithm(long unsigned int index) {
    customCout("SIMULANDO " + algorithms[index].first + "\n\n", BRIGHT_YELLOW);
    Kernel kernel(algorithms[index].second);
    kernel.run();
    Analyzer analyzer;
    analyzer.analyze(&kernel);
    customCout("FIM DA SIMULACAO\n\n", BRIGHT_YELLOW);

}