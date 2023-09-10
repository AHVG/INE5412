#ifndef _H_PROCESS_FACTORY
#define _H_PROCESS_FACTORY

#include <string>
#include "process.h"


class ProcessFactory {

private:


public:

    ProcessFactory();
    ~ProcessFactory();

    Process *createProcess(int _id, int _start, int _duration, int _priority);

    std::vector<Process *> createProcesses(std::vector<std::vector<int>>  lines);

};

#endif