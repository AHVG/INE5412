
#include <vector>

#include "context.h"


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

const long int *Context::getGpr() const {
    return gpr;
}

void Context::setSP(long int _SP) {
    SP = _SP;
}

void Context::setPC(long int _PC) {
    PC = _PC;
}

void Context::setstatus(long int _status) {
    status = _status;
}
