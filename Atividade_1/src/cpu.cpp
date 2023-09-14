
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

void INE5412::loadProcess(Process *newProcess) {
    if (newProcess) process_context = newProcess->getContext();
    process = newProcess;
}

Process *INE5412::unloadProcess() {
    timeRunningCurrentProcess = 0;
    Process *aux = process;
    process = nullptr;
    process_context = nullptr;
    return aux;
}

Process *CPU::switchProcess(Process *newProcess) {
    // Essa troca de ponteiro seria o equivalente ao real de trocar de contexto
    Process *oldProcess = unloadProcess();
    loadProcess(newProcess);
    return oldProcess;
}

void INE5412::execute(){
    if (process) {
        std::array<unsigned char, 8> aux;
        for (int i = 0; i < 8; i++) aux[i] = rand() % 256;
        Register rAux(aux);
        process_context->setPC(rAux);
        for (int i = 0; i < 8; i++) aux[i] = rand() % 256;
        rAux.setBytes(aux);
        process_context->setSP(rAux);
        for (int i = 0; i < 8; i++) aux[i] = rand() % 256;
        rAux.setBytes(aux);
        process_context->setStatus(rAux);
        for (int i = 0; i < 8; i++) aux[i] = rand() % 256;
        rAux.setBytes(aux);
        for (int i = 0; i < 6; i++) process_context->setGpr(i, rAux);
        timeRunningCurrentProcess++;
        process->incrementExecutedTime();
    }
    runningTime++;
}

int CPU::empty() {
    return !process;
}
