
#include <iostream>

#include "process.h"

// Classe responsável pelos processos
Process::Process(int _id, int _start, int _duration, int _priority) {
    id = _id;
    
    start = _start;
    duration = _duration;
    priority = _priority;

    end = 0;
    currentState = NOVO;
    executedTime = 0;

    context = new Context<6>();
}

Process::~Process() {
    delete context;
}

int Process::getId() const {
    return id;
}

int Process::getStart() const {
    return start;
}

int Process::getEnd() const {
    return end;
}

int Process::getDuration() const {
    return duration;
}

int Process::getPriority() const {
    return priority;
}

State Process::getCurrentState() const {
    return currentState;
}

int Process::getExecutedTime() const {
    return executedTime;
}

Context<6> *Process::getContext() const {
    return context;
}

void Process::setId(int _id) {
    id = _id;
}

void Process::setStart(int _start) {
    start = _start;
}

void Process::setEnd(int _end) {
    end = _end;
}

void Process::setDuration(int _duration) {
    duration = _duration;
}

void Process::setPriority(int _priority) {
    priority = _priority;
}

void Process::setCurrentState(State _currentState) {
    currentState = _currentState;
}

void Process::setExecutedTime(int _executedTime) {
    executedTime = _executedTime;
}

int Process::finished() const {
    return getDuration() <= getExecutedTime(); 
}

void Process::incrementExecutedTime() {    
    setExecutedTime(getExecutedTime() + 1);
}

// Método que retorna os dados de cada processo
std::ostream &operator<<(std::ostream& os, const Process& p) {
    os << "ID: " << p.getId() << ", Start: " << p.getStart() << ", Duration: " << p.getDuration() << ", Priority: " << p.getPriority() << ", Executed Time: " << p.getExecutedTime() << ", Current State: " << p.getCurrentState();
    return os;
}
