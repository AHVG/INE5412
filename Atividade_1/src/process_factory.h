#ifndef _H_PROCESS_FACTORY
#define _H_PROCESS_FACTORY

#include <string>
#include "process.h"
#include "file.h"


class ProcessFactory {

private:

    long long unsigned int id = 0;

public:

    ProcessFactory();
    ~ProcessFactory();

    std::vector<Process *> createProcesses(std::vector<ProcessParams *> processesParams);

};

#endif