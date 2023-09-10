#ifndef _H_KERNEL
#define _H_KERNEL

#include <algorithm>

#include "scheduling_algorithm.h"
#include "process_factory.h"
#include "file_reader.h"
#include "scheduler.h"
#include "process.h"
#include "cpu.h"


class Kernel {

private:

    std::vector<Process *> executedProcesses;
    std::vector<Process *> readyProcesses;
    std::vector<Process *> newProcesses;
    std::vector<Process *> PCB;
    Process *currentProcessRunning;
    
    ProcessFactory factory;
    Scheduler *scheduler;
    FileReader reader;
    CPU cpu;
    
    int clock;
    int contextSwitches;

    void initialize();  // Criará os processos e etc
    void close();       // Destrói tudo que foi criado
    
    void updateReadyProcesses();
    void update();
    
    void printState();

public:
    Kernel(SchedulingAlgorithm *algorithm);
    ~Kernel();

    void run();         // Executa os processo

    // TODO Será que eu faço para todos o get?
    std::vector<Process *> getExecutedProcesses() const;
    std::vector<Process *> getReadyProcesses() const;
    std::vector<Process *> getNewProcesses() const;
    std::vector<Process *> getPCB() const;

    int getClock() const;
    int getContextSwitches() const;

};


#endif
