#ifndef _H_PROCESS_FACTORY
#define _H_PROCESS_FACTORY
#include "process.h"
#include <string>

class ProcessFactory {

private:

public:
    ProcessFactory(){};

    ~ProcessFactory(){};
    public:
    Process* createProcess(int _id, int _start, int _duration, int _priority){
        return new Process(_id, _start, _duration, _priority);
    }
    std::vector<Process *> createProcess(std::vector<std::string> lines){
        std::vector<Process *> processes;
        int id = 1;
        for(int i = 0; i < lines.size(); i++){
                std::vector<int> list;
                for(int j = 0; j < 3; j++){
                    list.push_back(lines[i][j]);
                }
                Process* process = createProcess(id, list[0], list[1], list[2]);
                id++;
                processes.push_back(process);
        }
    }

};

#endif