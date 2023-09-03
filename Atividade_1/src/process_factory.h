#ifndef _H_PROCESS_FACTORY
#define _H_PROCESS_FACTORY

#include <string>
#include "process.h"


class ProcessFactory {

private:


public:

    ProcessFactory(){};
    ~ProcessFactory(){};

    Process* createProcess(int _id, int _start, int _duration, int _priority){
        return new Process(_id, _start, _duration, _priority);
    };

    std::vector<Process *> createProcesses(std::vector<std::string> lines){
        std::vector<Process *> processes;
        
        for(long unsigned int i = 0; i < lines.size(); i++) {
            processes.push_back(createProcess(i + 1, lines[i][0] - '0', lines[i][1] - '0', lines[i][2] - '0'));
        }
        return processes;
    };

};

#endif