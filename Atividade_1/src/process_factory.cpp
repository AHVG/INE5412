
#include <vector>
#include <string>

#include "process_factory.h"
#include "process.h"
#include "file.h"


// Classe Factory responsável pela criação das instâncias de Process
ProcessFactory::ProcessFactory() {}
ProcessFactory::~ProcessFactory() {}

// Método que cria processos a partir do arquivo de entrada
std::vector<Process *> ProcessFactory::createProcesses(std::vector<ProcessParams *> processesParams){
    std::vector<Process *> processes;
    for(auto pp : processesParams) processes.push_back(new Process(id++, pp->getCreationTime(), pp->getDuration(), pp->getPriority()));
    return processes;
}
