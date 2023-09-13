
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
    if (newProcess) process_context = newProcess->getContext();
    process = newProcess;
}

Process *CPU::unloadProcess() {
    timeRunningCurrentProcess = 0;
    Process *aux = process;
    process = nullptr;
    process_context = nullptr;
    return aux;
}

Process *CPU::switchProcess(Process *newProcess) {
    Process *oldProcess = unloadProcess();
    loadProcess(newProcess);
    return oldProcess;
}

void CPU::execute(){
    if (process) {
        process_context->setPC(process_context->getPC() + 1);
        process_context->setStatus(1);
        process_context->setSP(process_context->getSP() - 1);
        timeRunningCurrentProcess++;
        process->setExecutedTime(process->getExecutedTime() + 1);
        for(int i = 0; i < 6; i++) {
            process_context->setGpr(i, process_context->getGpr(i) + rand() % 100);
        }
    }
    runningTime++;
}

int CPU::empty() {
    return !process;
}
