#ifndef _H_PROCESS
#define _H_PROCESS

#include <iostream>


enum State {NOVO, PRONTO, EXECUTANDO, TERMINADO};

class Process {

private:

    int id;
    int start, end;
    int duration;
    int priority;
    State currentState;
    int executedTime;

public:

    Process(int _id, int _start, int _duration, int _priority){
        id = _id;
        
        start = _start;
        duration = _duration;
        priority = _priority;

        end = -1;
        currentState = NOVO;
        executedTime = 0;

    };

    ~Process(){

    };

    int getId() const { return id; };
    int getStart() const { return start; };
    int getEnd() const { return end; };
    int getDuration() const { return duration; };
    int getPriority() const { return priority; };
    State getCurrentState() const { return currentState; };
    int getExecutedTime() const { return executedTime; };


	friend std::ostream &operator<<(std::ostream& os, const Process& p) {
		os << "ID: " << p.getId() << ", Start: " << p.getStart() << ", Duration: " << p.getDuration() << ", Priority: " << p.getPriority() << std::endl;
		return os;
	}

};

#endif