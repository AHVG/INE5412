
#include <vector>

#include "context.h"

// Classe responsável por guardar o contexto de cada processo

Context::Context(Register _SP, Register _PC, Register _status) : SP(_SP), PC(_PC), status(_status) {}

Context::Context() {}

Context::~Context() {}

Register Context::getSP() const { 
    return SP;
}

Register Context::getPC() const {
    return PC;
}

Register Context::getStatus() const {
    return status;
}

Register Context::getGpr(int index) const {
    return gpr[index % 6];
}

void Context::setGpr(int index, Register value) {
    gpr[index % 6] = value;
}

void Context::setSP(Register _SP) {
    SP = _SP;
}

void Context::setPC(Register _PC) {
    PC = _PC;
}

void Context::setStatus(Register _status) {
    status = _status;
}
