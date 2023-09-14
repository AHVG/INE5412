#ifndef _H_CPU
#define _H_CPU

#include "process.h"
#include "context.h"


class CPU {

protected:

    Process *process;
    Context *process_context;
    int runningTime;
    int timeRunningCurrentProcess;
    int quantum;

public:

    CPU();
    ~CPU();

    Process *getProcess() const;
    int getRunningTime() const;
    int getTimeRunningCurrentProcess() const;
    int getQuantum() const;

    void setQuantum(int quantum);

    virtual void loadProcess(Process *newProcess) = 0;
    virtual Process *unloadProcess() = 0;
    Process *switchProcess(Process *newProcess);

    virtual void execute() = 0;

    int empty();

};

class INE5412 : public CPU {

public:

    void loadProcess(Process *newProcess) override;
    Process *unloadProcess() override;

    void execute() override;

};

#endif
