
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "file.h"


ProcessParams::ProcessParams(int c, int d, int p) { 
    creation_time = c;
    duration = d;
    priority = p;
}

std::ostream &operator<<(std::ostream& os, const ProcessParams& p) {
    os << "Creation time = " << p.creation_time << " duration = " << p.duration << " priority = " << p.priority << std::endl;
    return os;
}

int ProcessParams::getCreationTime() const {
    return creation_time;
}

int ProcessParams::getDuration() const {
    return duration;
}

int ProcessParams::getPriority() const {
    return priority;
}

File::File() {
    myfile.open("entrada.txt");
    if (!myfile.is_open()) {
        std::cout << "Erro ao abrir o arquivo!\n";
    }
}


File::~File() {
    for(long unsigned int i = 0; i < processes.size() ; i++) {
        ProcessParams *p = processes[i];
        delete p;
    }
}

void File::read_file() {

    int a, b, c;
    
    if (!myfile.is_open()) {
        std::cout << "Arquivo não está aberto!" << std::endl;
    }
    
    while (myfile >> a >> b >> c) {
        ProcessParams *p = new ProcessParams(a, b, c);
        processes.push_back(p);
    }

    std::cout << "Quantidade de processos lidos do arquivo: " << processes.size() << std::endl;
}

void File::print_processes_params() {
    std::vector<ProcessParams *>::iterator iter = processes.begin();

    for(; iter < processes.end(); iter++) {
        ProcessParams *p = *iter;
        std::cout << *p;
    }
}

std::vector<ProcessParams *> File::getProcesses() const {
    return processes;
}
