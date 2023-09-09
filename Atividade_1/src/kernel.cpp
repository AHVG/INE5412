
#include <iostream>
#include <algorithm>

#include "process.h"
#include "kernel.h"


Kernel::Kernel() {}
Kernel::~Kernel() {}

void Kernel::initialize() {
    // TODO: Verificar se os objetos retornados são desalocados
    std::cout << "Inicializando kernel...\n\n";
    
    std::cout << "Lendo arquivo...\n";
    std::vector<std::string> lines = reader.read("./entrada/entrada.txt");
    for (long unsigned int i = 0; i < lines.size(); i++) std::cout << lines[i] << std::endl;

    std::cout << std::endl;
    
    std::cout << "Criando processos...\n";
    processes = factory.createProcesses(lines);
    for (long unsigned int i = 0; i < processes.size(); i++) std::cout << *processes[i] << std::endl;

    std::cout << std::endl;

    clock = 0;
    updateReadyProcesses();
}

void Kernel::run() { 
    std::cout << "Executando os processo...\n\n";

    while (!processes.empty() || !readyProcesses.empty() || !cpu.empty()) {
        if (scheduler.isItTimeToSwitch(&cpu, readyProcesses)) {
            if (!cpu.empty()) {
                Process *p = cpu.unloadProcess();
                readyProcesses.push_back(p);
            }

            Process *p = scheduler.getNextProcess(readyProcesses);

            cpu.loadProcess(p);
        }

        cpu.execute(1);

        std::cout << clock << "-" << clock + 1 << ": " << *cpu.getProcess() << std::endl;

        clock++;
        updateReadyProcesses();

        // TODO tirar isso quando tiver tudo mec 
        if (clock > 20)
            break;
    }
    std::cout << std::endl;
}

void Kernel::close() {
    std::cout << "Encerrando kernel...\n\n";
    for (long unsigned int i = 0; i < executedProcesses.size(); i++) delete executedProcesses[i];
}

void Kernel::updateReadyProcesses() {
    int c = clock;
    std::copy_if(processes.begin(), processes.end(), std::back_inserter(readyProcesses), [c](Process *p) {
        int result = p->getStart() == c;
        if (result) p->setCurrentState(PRONTO);
        return result;
    });

    auto newEnd = std::remove_if(processes.begin(), processes.end(), [c](Process *p) {
        return p->getStart() == c;
    });

    // Redimensione o vetor para o novo tamanho após a filtragem
    processes.resize(std::distance(processes.begin(), newEnd));
}
