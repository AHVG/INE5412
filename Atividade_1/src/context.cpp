#include "context.h"

// Classe responsável por guardar o contexto de cada processo

template <int numGPRs>
Context<numGPRs>::Context(Register _SP, Register _PC, Register _status) : SP(_SP), PC(_PC), status(_status) {}

template <int numGPRs>
Context<numGPRs>::Context() {}

template <int numGPRs>
Context<numGPRs>::~Context() {}

template <int numGPRs>
Register Context<numGPRs>::getSP() const { 
    return SP;
}

template <int numGPRs>
Register Context<numGPRs>::getPC() const {
    return PC;
}

template <int numGPRs>
Register Context<numGPRs>::getStatus() const {
    return status;
}

template <int numGPRs>
Register Context<numGPRs>::getGpr(int index) const {
    return GPRs[index % 6];
}

template <int numGPRs>
void Context<numGPRs>::setGpr(int index, Register value) {
    GPRs[index % 6] = value;
}

template <int numGPRs>
void Context<numGPRs>::setSP(Register _SP) {
    SP = _SP;
}

template <int numGPRs>
void Context<numGPRs>::setPC(Register _PC) {
    PC = _PC;
}
template <int numGPRs>
void Context<numGPRs>::setStatus(Register _status) {
    status = _status;
}

template class Context<6>;