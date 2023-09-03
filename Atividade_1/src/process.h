#ifndef _H_PROCESS
#define _H_PROCESS


enum State {NOVO, PRONTO, EXECUTANDO, TERMINADO};

class Process {

private:

    int id;
    int start, end;
    int duration;
    int priority;
    State current_state;
    int executed_time;

public:

    Process(int _id, int _start, int _duration, int _priority){
        id = _id;
        
        start = _start;
        duration = _duration;
        priority = _priority;

        end = -1;
        current_state = NOVO;
        executed_time = 0;

    };

    ~Process(){

    };


};

#endif