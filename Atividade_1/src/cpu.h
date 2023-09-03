#ifndef _H_CPU
#define _H_CPU

#include "process.h"
#include "context.h"


class CPU {

private:

    Process *process;

public:

    CPU(){};
    ~CPU(){};

    void loadProcess(Process *p) {

    }

    Process *unloadProcess() {

    }

    void execute(){
        
        // TODO processamento

    };

};

#endif
