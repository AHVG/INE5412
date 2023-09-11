
#include "cpu.h"
#include "process.h"


CPU::CPU() {
    process = nullptr;
    runningTime = 0;
    timeRunningCurrentProcess = 0;
    quantum = 2;
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

int CPU::getQuantum() const {
    return quantum;
}

void CPU::setQuantum(int _quantum) {
    quantum = _quantum;
}

void CPU::loadProcess(Process *newProcess) {
    if (newProcess) context = newProcess->getContext();
    process = newProcess;
}

Process *CPU::unloadProcess() {
    timeRunningCurrentProcess = 0;
    Process *aux = process;
    process = nullptr;
    context = nullptr;
    return aux;
}

Process *CPU::switchProcess(Process *newProcess) {
    Process *oldProcess = unloadProcess();
    loadProcess(newProcess);
    return oldProcess;
}

void CPU::execute(){
    if (process) {
        context->setPC(context->getPC() + 1);
        context->setStatus(1);
        context->setSP(context->getSP() - 1);
        timeRunningCurrentProcess++;
        process->setExecutedTime(process->getExecutedTime() + 1);
        // TODO fazer alguma manipulação aletoria do contexto
    }
    runningTime++;
}

int CPU::empty() {
    return !process;
}
