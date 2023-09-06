
#include "cpu.h"
#include "process.h"


CPU::CPU() {
    process = nullptr;
    runningTime = 0;
    timeRunningCurrentProcess = 0;
    processDurationTime = 0;
}

CPU::~CPU() {}

Process *CPU::getProcess() const {
    return process;
}

int CPU::getRunningTime() const { 
    return runningTime;
}

int CPU::getTimeRunningCurrentProcess() const {
    return timeRunningCurrentProcess;
}

int CPU::getProcessDurationTime() const {
    return processDurationTime;
}

void CPU::loadProcess(Process *p, int executionDuration) {
    process = p;
    processDurationTime = executionDuration;
    process->setCurrentState(EXECUTANDO);
}

Process *CPU::unloadProcess() {
    timeRunningCurrentProcess = 0;
    if (process->finished()) process->setCurrentState(TERMINADO);
    else process->setCurrentState(PRONTO);
    Process *aux = process;
    process = nullptr;
    return aux;
}

void CPU::execute(int dt){
    if (process) {
        timeRunningCurrentProcess += dt;
        process->setExecutedTime(process->getExecutedTime() + dt);
    }
    runningTime += dt;
}

int CPU::finishExecuting() {
    return timeRunningCurrentProcess == processDurationTime;
}

int CPU::empty() {
    return !process;
}
