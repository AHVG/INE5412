#ifndef _H_KERNEL
#define _H_KERNEL

#include "file_reader.h"
#include "process_factory.h"
#include "process.h"

class Kernel {

private:

    FileReader reader;
    ProcessFactory factory;
    std::vector<Process *> processes;
    std::vector<Process *> ready_processes;
    std::vector<Process *> executed_processes;

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

    };    // Criará os processos e etc

    int run() { 

        while(!processes.empty() && !ready_processes.empty()) {
            // Organizar a lista de acordo com o algoritmo
            // Obter o próximo processo
            // Executá-lo
            // Verificar se ele terminou de se executado

        }
        return 1;
    }; // Executa os processo
    
    void close() {
        std::cout << "Encerrando kernel...\n\n";
        for (long unsigned int i = 0; i < processes.size(); i++) delete processes[i];
    };         // Destrói tudo que foi criado
};

#endif
