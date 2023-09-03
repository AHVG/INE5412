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

public:
    Kernel() {};
    ~Kernel() {};

    void initialize() {
        std::cout << "Inicializando kernel..." << std::endl;
        std::vector<std::string> lines = reader.read("../entrada/entrada.txt");
        // for (long unsigned int i = 0; i < lines.size(); i++) std::cout << lines[i] << std::endl;
        processes = factory.createProcesses(lines);
        for (long unsigned int i = 0; i < processes.size(); i++) std::cout << *processes[i] << std::endl;

    };    // Criará os processos e etc

    int run() { return 1; }; // Executa os processo
    
    void close() {
        for (long unsigned int i = 0; i < processes.size(); i++) delete processes[i];
    };         // Destrói tudo que foi criado
};

#endif
