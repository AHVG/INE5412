#ifndef _H_CPU
#define _H_CPU

#include "process.h"


class CPU {

private:

    Process *process;
    int runningTime;
    int timeRunningCurrentProcess;

public:

    CPU();
    ~CPU();

    Process *getProcess() const;
    int getRunningTime() const;
    int getTimeRunningCurrentProcess() const;

    // TODO Load o contexto ou o processo? Eu acho que o processo torna o código mais fácil, mas faz mais sentido o contexto
    void loadProcess(Process *newProcess);
    Process *unloadProcess();
    Process *switchProcess(Process *newProcess);

    void execute();

    int empty();

};

#endif
