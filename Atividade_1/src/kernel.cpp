
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cmath>


#include "scheduling_algorithm.h"
#include "process.h"
#include "kernel.h"
#include "utils.h"
#include "file.h"

// Classe responsável por gerenciar o kernel
Kernel::Kernel(SchedulingAlgorithm *algorithm) {
    scheduler = new Scheduler(algorithm);
    currentProcessRunning = nullptr;
    clock = 0;
    contextSwitches = 0;
}

Kernel::~Kernel() {
    for (long unsigned int i = 0; i < PCB.size(); i++) delete PCB[i];
    delete scheduler;
}

// Método que inicializa o kernel
// Lê o arquivo de entrada e cria os processos
void Kernel::initialize() {
    customCout("Inicializando kernel...\n\n", BRIGHT_GREEN);

    setColor(WHITE);
    std::cout << "Arquivo " << BRIGHT_WHITE << "entrada.txt\n\n" << WHITE;
    file.read_file();
    std::vector<ProcessParams *> lines = file.getProcesses();
    file.print_processes_params();
    resetColor();
    
    std::cout << "\nProcessos \n\n";
    newProcesses = factory.createProcesses(lines);
    // Organizar os processos de tal forma que o primeiro do vetor sempre é o que foi criado primeiro
    // deixa a saida toda desconfigurada, com P1 podendo estar no meio da tela. Assim, seria também necessário
    // setar o id novamente. No entanto, acredito mesmo que a ordem do vetor deve permanecer a mesma ordem
    // das linhas do arquivo .txt.
    PCB = newProcesses;
    for (auto p : PCB) std::cout << *p << std::endl;
    std::cout << std::endl;
    resetColor();

    clock = 0;
    contextSwitches = 0;
}

// Método responsável pela execucao do Kernel
// Executa os processos e gerencia o estado de cada um
void Kernel::run() { 
    initialize();
    customCout("Executando os processos...\n\n", BRIGHT_GREEN);

    while (1) {

        // Atualizando
        update();

        // Verificando se ja terminou tudo. Se sim, o kernel encerra
        if (newProcesses.empty() && readyProcesses.empty() && cpu.empty()) break;
        
        // Executando mais um ciclo do processo
        cpu.execute();

        // Contando mais um ciclo
        clock++;
    }
    customCout("\nEncerrando kernel...\n\n", BRIGHT_GREEN);
}

// Método responsável por atualizar o estado dos processsos
// Verifica se já é hora de trocar de processo
// Se for, troca de processo e gerencia o estado do processo atual
void Kernel::update() {
    // Atualizando lista de processos
    updateReadyProcesses();
    // Se for a hora de trocar, troca o processo e faz o gerenciamento do estado do processo atual
    if (scheduler->isItTimeToSwitch(&cpu, readyProcesses)) {
        if (currentProcessRunning) {
            if (currentProcessRunning->finished()) {
                executedProcesses.push_back(currentProcessRunning);
                currentProcessRunning->setEnd(clock);
                currentProcessRunning->setCurrentState(TERMINADO);
            } else {
                readyProcesses.push_back(currentProcessRunning);
                currentProcessRunning->setCurrentState(PRONTO);
            }
        }
        currentProcessRunning = scheduler->getNextProcess(readyProcesses);
        if (currentProcessRunning) {
            readyProcesses.erase(readyProcesses.begin());
            currentProcessRunning->setCurrentState(EXECUTANDO);
        }
        cpu.switchProcess(currentProcessRunning);
        contextSwitches++;
    }
    std::vector<State> line;
    for (auto p : PCB) line.push_back(p->getCurrentState());
    executionHistory.push_back(line);
}

// Método responsável por atualizar a lista de processos prontos
// Verifica se já é hora de adicionar um processo na lista de prontos
// Se for, adiciona o processo na lista de prontos e gerencia o estado do processo
void Kernel::updateReadyProcesses() {
    int c = clock;
    std::copy_if(newProcesses.begin(), newProcesses.end(), std::back_inserter(readyProcesses), [c](Process *p) {
        int result = p->getStart() == c;
        if (result) p->setCurrentState(PRONTO);
        return result;
    });

    auto newEnd = std::remove_if(newProcesses.begin(), newProcesses.end(), [c](Process *p) {
        return p->getStart() == c;
    });
    newProcesses.resize(std::distance(newProcesses.begin(), newEnd));

}

std::vector<std::vector<State>> Kernel::getExecutionHistory() const {
    return executionHistory;
}

std::vector<Process *> Kernel::getExecutedProcesses() const {
    return executedProcesses;
}

std::vector<Process *> Kernel::getReadyProcesses() const {
    return readyProcesses;
}

std::vector<Process *> Kernel::getNewProcesses() const {
    return newProcesses;
}

std::vector<Process *> Kernel::getPCB() const {
    return PCB;
}

int Kernel::getClock() const {
    return clock;
}

int Kernel::getContextSwitches() const {
    return contextSwitches;
}

