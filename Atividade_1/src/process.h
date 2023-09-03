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

    void setId(int _id) { id = _id; };
    void setStart(int _start) { start = _start; };
    void setEnd(int _end) { end = _end; };
    void setDuration(int _duration) { duration = _duration; };
    void setPriority(int _priority) { priority = _priority; };
    void setCurrentState(State _currentState) { currentState = _currentState; };
    void setExecutedTime(int _executedTime) { executedTime = _executedTime; };


	friend std::ostream &operator<<(std::ostream& os, const Process& p) {
		os << "ID: " << p.getId() << ", Start: " << p.getStart() << ", Duration: " << p.getDuration() << ", Priority: " << p.getPriority();
		return os;
	}

};

#endif