#ifndef _H_CPU
#define _H_CPU

#include "process.h"


class CPU {

private:

    Process *process;
    int runningTime;
    int timeRunningCurrentProcess;
    int processDurationTime;

public:

    CPU();
    ~CPU();

    Process *getProcess() const;
    int getRunningTime() const;
    int getTimeRunningCurrentProcess() const;
    int getProcessDurationTime() const;

    void loadProcess(Process *p, int executionDuration);

    Process *unloadProcess();

    void execute(int dt);

    int finishExecuting();

    int empty();

};

#endif
