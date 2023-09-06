#ifndef _H_PROCESS
#define _H_PROCESS

#include <iostream>
#include "context.h"


enum State {NOVO, PRONTO, EXECUTANDO, TERMINADO};

class Process {

private:

    int id;
    int start, end;
    int duration;
    int priority;
    State currentState;
    int executedTime;
    Context *context;

public:

    Process(int _id, int _start, int _duration, int _priority);

    ~Process();

    int getId() const;
    int getStart() const;
    int getEnd() const;
    int getDuration() const;
    int getPriority() const;
    State getCurrentState() const;
    int getExecutedTime() const;

    void setId(int _id);
    void setStart(int _start);
    void setEnd(int _end);
    void setDuration(int _duration);
    void setPriority(int _priority);
    void setCurrentState(State _currentState);
    void setExecutedTime(int _executedTime);

    int finished() const;

	friend std::ostream &operator<<(std::ostream& os, const Process& p);
};

#endif