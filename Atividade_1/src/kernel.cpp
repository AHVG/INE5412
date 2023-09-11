
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cmath>


#include "scheduling_algorithm.h"
#include "analyzer.h"
#include "process.h"
#include "kernel.h"
#include "utils.h"


Kernel::Kernel(SchedulingAlgorithm *algorithm) {
    scheduler = new Scheduler(algorithm);
    currentProcessRunning = nullptr;
    clock = 0;
    contextSwitches = 0;
}

Kernel::~Kernel() {
    delete scheduler;
}

void Kernel::initialize() {
    customCout("Inicializando kernel...\n\n", BRIGHT_GREEN);

    setColor(WHITE);
    std::cout << "Arquivo " << BRIGHT_WHITE << "entradas/entrada.txt\n\n" << WHITE;
    std::vector<std::vector<int>> lines = reader.read("entradas/entrada.txt");
    for (long unsigned int i = 0; i < lines.size(); i++) {
        int width = std::log10(lines.size()) + 1;
        std::cout << std::setw(width) << i + 1 << "   ";
        for (auto v : lines[i]) std::cout << v << " ";
        std::cout << std::endl;
    }
    
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

void Kernel::run() { 
    initialize();
    customCout("Executando os processos...\n\n", BRIGHT_GREEN);

    int width = std::log10(PCB.size()) + 1;
    setColor(BRIGHT_WHITE);
    std::cout << "tempo ";
    for (auto p : PCB) std::cout << "P" << std::setw(width) << std::setfill('0') << p->getId() << " ";
    std::cout << std::setfill(' ') << std::endl;
    resetColor();

    while (1) {

        // Atualizando
        update();

        // Verificando se ja terminou tudo. Se sim, o kernel encerra
        if (newProcesses.empty() && readyProcesses.empty() && cpu.empty()) break;
        
        // Executando mais um ciclo do processo
        cpu.execute();

        // Mostrando no console o atual estado dos processos 
        printState();

        // Contando mais um ciclo
        clock++;
    }
    close();
}

void Kernel::close() {
    customCout("\nEncerrando kernel...\n\n", BRIGHT_GREEN);
    Analyzer analyzer;
    analyzer.analyze(this);
    for (long unsigned int i = 0; i < PCB.size(); i++) delete PCB[i];
}

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
        if (currentProcessRunning) currentProcessRunning->setCurrentState(EXECUTANDO);
        cpu.switchProcess(currentProcessRunning);
        contextSwitches++;
    }
}

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

void Kernel::printState() {
    std::string interval = std::to_string(clock) + "-" + std::to_string(clock + 1);
    setColor(BRIGHT_WHITE);
    std::cout << std::setw(5) << interval << " ";
    resetColor();
    
    int width = std::log10(PCB.size()) + 1;
    for (auto p : PCB) {
        int state = p->getCurrentState();
        if (state == EXECUTANDO) {customCout("  ", WEAK_GREEN_BACKGROUND); std::cout << std::setw(width) << " ";}
        else if (state == NOVO) std::cout << std::setw(width + 2) << " ";
        else if (state == PRONTO) {customCout("  ", WEAK_RED_BACKGROUND);  std::cout << std::setw(width) << " ";}
        else std::cout << std::setw(width + 2) << " ";
    }
    std::cout << std::endl;
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

