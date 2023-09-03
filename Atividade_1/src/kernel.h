#ifndef _H_KERNEL
#define _H_KERNEL

#include <algorithm>
#include "file_reader.h"
#include "process_factory.h"
#include "process.h"
#include "cpu.h"

class Kernel {

private:

    FileReader reader;
    ProcessFactory factory;
    std::vector<Process *> processes;
    std::vector<Process *> readyProcesses;
    std::vector<Process *> executedProcesses;
    CPU cpu;
    int clock;

public:
    Kernel() {};
    ~Kernel() {};

    void initialize() {
        // TODO: Verificar se os objetos retornados são desalocados
        std::cout << "Inicializando kernel...\n\n";
        
        std::cout << "Lendo arquivo...\n";
        std::vector<std::string> lines = reader.read("../entrada/entrada.txt");
        for (long unsigned int i = 0; i < lines.size(); i++) std::cout << lines[i] << std::endl;

        std::cout << std::endl;
        
        std::cout << "Criando processos...\n";
        processes = factory.createProcesses(lines);
        for (long unsigned int i = 0; i < processes.size(); i++) std::cout << *processes[i] << std::endl;

        std::cout << std::endl;

        clock = 0;
        updateReadyProcesses();
    }; // Criará os processos e etc

    void run() { 
        std::cout << "Executando os processo...\n\n";

        while (!processes.empty() || !readyProcesses.empty() || !cpu.empty()) {
            if (cpu.empty() && !readyProcesses.empty()) {
                // TODO: Arrumar para o escalonador
                Process *p = readyProcesses.at(0);
                readyProcesses.erase(readyProcesses.begin());
                int duration = p->getDuration() - p->getExecutedTime();

                cpu.loadProcess(p, duration);
            }

            cpu.execute(1);

            std::cout << clock << "-" << clock + 1 << ": " << *cpu.getProcess() << std::endl;

            if (cpu.finishExecuting()) {
                std::cout << "Trocando contexto..." << std::endl;
                Process *p = cpu.unloadProcess();

                if (p->getCurrentState() == PRONTO) {
                    readyProcesses.push_back(p);
                } else {
                    executedProcesses.push_back(p);
                    p->setEnd(clock);
                }

                if (!readyProcesses.empty()) {
                    // TODO: Arrumar para o escalonador
                    p = readyProcesses.at(0);
                    readyProcesses.erase(readyProcesses.begin());
                    int duration = p->getDuration() - p->getExecutedTime();

                    cpu.loadProcess(p, duration);
                }
            }

            clock++;
            updateReadyProcesses();

            if (clock > 20)
                break;
        }
        std::cout << std::endl;
    }; // Executa os processo
    
    void close() {
        std::cout << "Encerrando kernel...\n\n";
        for (long unsigned int i = 0; i < executedProcesses.size(); i++) delete executedProcesses[i];
    }; // Destrói tudo que foi criado

    void updateReadyProcesses() {
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
};

#endif
