#ifndef _H_CPU
#define _H_CPU

#include "process.h"
#include "context.h"


class CPU {

private:

    Process *process;
    Context *context;
    int runningTime;
    int timeRunningCurrentProcess;
    int quantum;

public:

    CPU();
    ~CPU();

    Process *getProcess() const;
    int getRunningTime() const;
    int getTimeRunningCurrentProcess() const;
    int getQuantum() const;

    // TODO Load o contexto ou o processo? Eu acho que o processo torna o código mais fácil, mas faz mais sentido o contexto
    // PROBLEMA terá que refatorar o scheduling_algorithm
    void loadProcess(Process *newProcess);
    void setQuantum(int quantum);
    Process *unloadProcess();
    Process *switchProcess(Process *newProcess);

    void execute();

    int empty();

};

#endif
