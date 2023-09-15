#ifndef _H_KERNEL
#define _H_KERNEL

#include <algorithm>

#include "scheduling_algorithm.h"
#include "process_factory.h"
#include "file.h"
#include "scheduler.h"
#include "process.h"
#include "cpu.h"


class Kernel {

private:

    std::vector<std::vector<State>> executionHistory;
    std::vector<Process *> executedProcesses;
    std::vector<Process *> readyProcesses;
    std::vector<Process *> newProcesses;
    std::vector<Process *> PCB;
    Process *currentProcessRunning;
    
    ProcessFactory factory;
    Scheduler *scheduler;
    File file;
    INE5412 cpu;
    
    int clock;
    int contextSwitches;

    // Criar um histórico do que foi executado, para que o analyzer faça a impressão da simulação?
    // Desacopla a lógica de print do kernel, mas será que faz sentido?

    void initialize();  // Criará os processos e etc
    
    void updateReadyProcesses();
    void update();
    
    void printState();

public:
    Kernel(SchedulingAlgorithm *algorithm);
    ~Kernel();

    void run();         // Executa os processo

    std::vector<std::vector<State>> getExecutionHistory() const;
    std::vector<Process *> getExecutedProcesses() const;
    std::vector<Process *> getReadyProcesses() const;
    std::vector<Process *> getNewProcesses() const;
    std::vector<Process *> getPCB() const;

    int getClock() const;
    int getContextSwitches() const;

};


#endif
