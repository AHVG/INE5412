#ifndef _H_KERNEL
#define _H_KERNEL

#include <algorithm>

#include "process_factory.h"
#include "file_reader.h"
#include "scheduler.h"
#include "process.h"
#include "cpu.h"

void printProcesses(std::vector<Process *> processes, std::string processesName);

class Kernel {

private:

    std::vector<Process *> executedProcesses;
    std::vector<Process *> readyProcesses;
    std::vector<Process *> processes;
    
    ProcessFactory factory;
    Scheduler scheduler;
    FileReader reader;
    CPU cpu;
    
    int clock;

public:
    Kernel();
    ~Kernel();

    void initialize(); // Criará os processos e etc

    void run(); // Executa os processo
    
    void close(); // Destrói tudo que foi criado

    void updateReadyProcesses();
};

#endif
