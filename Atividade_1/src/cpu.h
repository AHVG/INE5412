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

    CPU() {
        process = nullptr;
        runningTime = 0;
        timeRunningCurrentProcess = 0;
        processDurationTime = 0;
    };
    ~CPU() {};

    Process *getProcess() const { return process; };
    int getRunningTime() const { return runningTime; };
    int getTimeRunningCurrentProcess() const { return timeRunningCurrentProcess; };
    int getProcessDurationTime() const { return processDurationTime; };

    void loadProcess(Process *p, int executionDuration) {
        process = p;
        processDurationTime = executionDuration;
        process->setCurrentState(EXECUTANDO);
    };

    Process *unloadProcess() {
        timeRunningCurrentProcess = 0;
        if (process->finished()) process->setCurrentState(TERMINADO);
        else process->setCurrentState(PRONTO);
        Process *aux = process;
        process = nullptr;
        return aux;
    };

    void execute(int dt){
        if (process) {
            timeRunningCurrentProcess += dt;
            process->setExecutedTime(process->getExecutedTime() + dt);
        }
        runningTime += dt;
    };

    int finishExecuting() {
        return timeRunningCurrentProcess == processDurationTime;
    }

    int empty() {
        return !process;
    }

};

#endif
