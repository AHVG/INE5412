
#include <algorithm>
#include <iostream>
#include <iomanip>

#include "analyzer.h"
#include "process.h"
#include "kernel.h"


Kernel::Kernel() {}
Kernel::~Kernel() {}

void Kernel::initialize() {
    // TODO: Verificar se os objetos retornados são desalocados
    std::cout << "Inicializando kernel...\n\n";
    
    std::cout << "Lendo arquivo...\n\n";
    std::vector<std::vector<int>> lines = reader.read("entrada.txt");
    std::cout << "Linhas do arquivo:" << std::endl;
    for (long unsigned int i = 0; i < lines.size(); i++) {
        std::cout << i + 1 << "   ";
        for (auto v : lines[i]) std::cout << v << " ";
        std::cout << std::endl;
    }

    std::cout << std::endl;
    
    std::cout << "Criando processos...\n\n";
    newProcesses = factory.createProcesses(lines);
    // TODO organizar a lista em ordem de criação ?
    PCB = newProcesses;
    printProcesses(newProcesses, "Processos criados");
    std::cout << std::endl;

    clock = 0;
    contextSwitches = 0;
}

void Kernel::run() { 
    std::cout << "Executando os processos...\n\n";

    // TODO boto fé em colocar cor no console
    std::cout << "tempo ";
    for (auto p : PCB) std::cout << "P" << p->getId() << " ";
    std::cout << std::endl;
    
    while (1) {
        // Atualizando lista de processos
        updateReadyProcesses();

        // Se for a hora de trocar, troca o processo
        if (scheduler.isItTimeToSwitch(&cpu, readyProcesses)) {
            // Se a cpu estiver vazia, então descarrega processo
            if (!cpu.empty()) {
                Process *p = cpu.unloadProcess();
                if (p->getCurrentState() != TERMINADO) readyProcesses.push_back(p);
                else {executedProcesses.push_back(p); p->setEnd(clock);}
            }
            // Carrega o próximo processo na cpu
            Process *nextProcess = scheduler.getNextProcess(readyProcesses);
            if (nextProcess) cpu.loadProcess(nextProcess);
            contextSwitches++;
        }

        if (newProcesses.empty() && readyProcesses.empty() && cpu.empty()) break;
        
        // Executando processo 
        cpu.execute(1);

        // TODO boto fé em colocar cor no console
        std::string interval = std::to_string(clock) + "-" + std::to_string(clock + 1);
        std::cout << std::setw(5) << interval << "  ";
        for (auto p : PCB) {
            int state = p->getCurrentState();
            if (state == EXECUTANDO) std::cout << "## ";
            else if (state == NOVO) std::cout << "   ";
            else if (state == PRONTO) std::cout << "-- ";
            else std::cout << "   ";
        }
        std::cout << std::endl;

        // Contando mais um ciclo
        clock++;
    }
}

void Kernel::close() {
    std::cout << "\nEncerrando kernel...\n\n";
    Analyzer analyzer;
    analyzer.analyze(this);
    for (long unsigned int i = 0; i < PCB.size(); i++) delete PCB[i];
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

void printProcesses(std::vector<Process *> processes, std::string processesName) {
    std::cout << processesName << ":" << std::endl;
    for (auto p : processes) {
        std::cout << "      " << *p << std::endl;
    }
}