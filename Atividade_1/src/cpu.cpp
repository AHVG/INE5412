
#include "cpu.h"
#include "process.h"


CPU::CPU() {
    process = nullptr;
    runningTime = 0;
    timeRunningCurrentProcess = 0;
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

void CPU::loadProcess(Process *newProcess) {
    process = newProcess;
}

Process *CPU::unloadProcess() {
    timeRunningCurrentProcess = 0;
    Process *aux = process;
    process = nullptr;
    return aux;
}

Process *CPU::switchProcess(Process *newProcess) {
    Process *oldProcess = unloadProcess();
    loadProcess(newProcess);
    return oldProcess;
}

void CPU::execute(){
    if (process) {
        timeRunningCurrentProcess++;
        process->setExecutedTime(process->getExecutedTime() + 1);
        // TODO fazer alguma manipulação aletoria do contexto
    }
    runningTime++;
}

int CPU::empty() {
    return !process;
}
