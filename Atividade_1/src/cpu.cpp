
#include "cpu.h"
#include "process.h"

// Classe responsável por simular a CPU
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
// Carrega o processo na CPU, ou seja, coloca o processo que esta em execução na CPU
void CPU::loadProcess(Process *newProcess) {
    if (newProcess) context = newProcess->getContext();
    process = newProcess;
}

// Descarregar processo, ou seja, retira o processo que esta em execução da CPU
Process *CPU::unloadProcess() {
    timeRunningCurrentProcess = 0;
    Process *aux = process;
    process = nullptr;
    context = nullptr;
    return aux;
}
// Método responsável pela troca de processo, consequentemente, troca de contexto
Process *CPU::switchProcess(Process *newProcess) {
    Process *oldProcess = unloadProcess();
    loadProcess(newProcess);
    return oldProcess;
}

// Método responsável por executar o processo que esta na CPU
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
