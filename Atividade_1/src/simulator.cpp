
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
        customCout("OPCOES: 1 -> FCFS, 2 -> SJF, 3 -> PRIORITY, 4 -> PRIORITY WITH PREEMPTION,  5 -> ROUND ROBIN, 6 -> RODAR TODOS, -1 -> SAIR\n", BRIGHT_CYAN);
        
        int option;
        std::cin >> option;
        std::cout << std::endl;

        if (option == -1) break; // Usuário quer sair
        if (option < 1 || 6 < option) {customCout("OPCAO INVALIDA\n\n", BRIGHT_RED); continue;} // Opção não existe, tenta novamente

        if (option == 6) for (int i = 0; i < 5; i++) runAnAlgorithm(i);
        else runAnAlgorithm(option - 1);
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