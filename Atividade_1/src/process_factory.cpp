
#include <vector>
#include <string>

#include "process_factory.h"
#include "process.h"


// Classe Factory responsável pela criação das instâncias de Process
ProcessFactory::ProcessFactory() {}
ProcessFactory::~ProcessFactory() {}

Process *ProcessFactory::createProcess(int _id, int _start, int _duration, int _priority){
    return new Process(_id, _start, _duration, _priority);
}

// Método que cria processos a partir do arquivo de entrada
std::vector<Process *> ProcessFactory::createProcesses(std::vector<std::vector<int>> lines){
    std::vector<Process *> processes;
    for(long unsigned int i = 0; i < lines.size(); i++) processes.push_back(createProcess(i + 1, lines[i][0], lines[i][1], lines[i][2]));
    return processes;
}
