
#include <vector>
#include <string>

#include "process_factory.h"
#include "process.h"



ProcessFactory::ProcessFactory() {}
ProcessFactory::~ProcessFactory() {}

Process *ProcessFactory::createProcess(int _id, int _start, int _duration, int _priority){
    return new Process(_id, _start, _duration, _priority);
}

std::vector<Process *> ProcessFactory::createProcesses(std::vector<std::string> lines){
    std::vector<Process *> processes;
    
    for(long unsigned int i = 0; i < lines.size(); i++) {
        processes.push_back(createProcess(i + 1, lines[i][0] - '0', lines[i][1] - '0', lines[i][2] - '0'));
    }
    return processes;
}
