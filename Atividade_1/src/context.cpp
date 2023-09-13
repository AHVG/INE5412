
#include <vector>

#include "context.h"

// Classe responsável por guardar o contexto de cada processo

Context::Context(long int _SP, long int _PC, long int _status) : SP(_SP), PC(_PC), status(_status) {}

Context::~Context(){}

long int Context::getSP() const { 
    return SP;
}

long int Context::getPC() const {
    return PC;
}

long int Context::getStatus() const {
    return status;
}

long int Context::getGpr(int index) const {
    if (index >= 0 && index < 6) return gpr[index];
    else return -1;
}

void Context::setGpr(int index, long int value) {
    if(index >= 0 && index < 6) gpr[index] = value;
}

void Context::setSP(long int _SP) {
    SP = _SP;
}

void Context::setPC(long int _PC) {
    PC = _PC;
}

void Context::setStatus(long int _status) {
    status = _status;
}
