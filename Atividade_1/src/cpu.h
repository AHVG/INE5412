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

    void loadProcess(Process *p);
    Process *unloadProcess();

    void execute(int dt);

    int empty();

};

#endif
