#ifndef _H_KERNEL
#define _H_KERNEL

#include "file_reader.h"
#include "process_factory.h"


class Kernel {

private:
public:
    Kernel() {}
    ~Kernel() {}

    void initialize() {
        std::cout << "Inicializando kernel..." << std::endl;
        
        FileReader reader;
        std::vector<std::string> lines = reader.read("../entrada/entrada.txt");

        ProcessFactory factory;
        std::vector<Process *> process = 

    }    // Criará os processos e etc
    int run() { return 1; } // Executa os processo
    void close() {}         // Destrói tudo que foi criado
};

#endif
