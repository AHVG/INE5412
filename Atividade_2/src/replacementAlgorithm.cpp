
#include "replacementAlgorithm.h"

#include <algorithm>

ReplacementAlgorithm::ReplacementAlgorithm() : RAMFrames(0) {}


ReplacementAlgorithm::ReplacementAlgorithm(std::size_t _RAMFrames) : RAMFrames(_RAMFrames) {}


ReplacementAlgorithm::~ReplacementAlgorithm() {}


std::vector<std::size_t> ReplacementAlgorithm::getPages() const {
    return pages;
}

int ReplacementAlgorithm::full() {
    return pages.size() == RAMFrames;
}

FIFOAlgorithm::FIFOAlgorithm() : ReplacementAlgorithm() {}


FIFOAlgorithm::FIFOAlgorithm(std::size_t _RAMFrames) : ReplacementAlgorithm(_RAMFrames) {}


FIFOAlgorithm::~FIFOAlgorithm() {}


int FIFOAlgorithm::accessMemory(std::size_t page) {

    // FIFO: First In First Out
    // Caso page fault, retira o primeiro elemento da lista e insere o novo elemento no final da lista
    // Caso ele acessar uma pagina que ja estava na lista, nao faz nada

    auto it = std::find_if(pages.begin(), pages.end(), [page] (const std::size_t &p) {
        return p == page;
    });

    if (it == pages.end()) {
        if (full()) pages.erase(pages.begin());
        pages.push_back(page);
        return 0;
    }

    return 1;
}


LRUAlgorithm::LRUAlgorithm(std::size_t _RAMFrames) : ReplacementAlgorithm(_RAMFrames) {}


LRUAlgorithm::~LRUAlgorithm() {}


int LRUAlgorithm::accessMemory(std::size_t page) {

    // LRU: Least Recently Used
    // Caso page fault, retira o ultimo elemento da lista e insere o novo elemento no inicio da lista
    // Caso ele acessar uma pagina que ja estava na lista, joga esse elemento para o inicio da lista
 
    auto it = std::find_if(pages.begin(), pages.end(), [page] (const std::size_t &p) {
        return p == page;
    });

    if (it == pages.end()) {
        if (full()) pages.erase(pages.begin());
        pages.push_back(page);
        return 0;
    }
    std::size_t p = *it;
    pages.erase(it);
    pages.push_back(p);

    return 1;
}


OPTAlgorithm::OPTAlgorithm(std::size_t _RAMFrames, std::vector<std::size_t> _lines) : ReplacementAlgorithm(_RAMFrames), lines(_lines), currentLine(-1)  {}
OPTAlgorithm::OPTAlgorithm() : ReplacementAlgorithm() {}  

OPTAlgorithm::~OPTAlgorithm() {}


int OPTAlgorithm::accessMemory(std::size_t page) {

    // OPT: Optimal
    // Caso page fault, retira o elemento que vai demorar mais para ser acessado e insere o novo elemento no final da lista
    // Ou seja, o elemento com maior tag
    // Caso ele acessar uma pagina que ja estava na lista, nao faz nada

    currentLine++;
    auto it = std::find_if(pages.begin(), pages.end(), [page] (const std::size_t &p) {
        return p == page;
    });

    if(it != pages.end()){
        return 1;
    }
    if(!full()) {
        pages.push_back(page);
        return 0;
    }
    std::size_t pageToErase = 0;
    std::size_t distance = 0;
    for(std::size_t i : pages){
        std::size_t nextOcurrence = findNextOcurrence(lines, currentLine, i);
        if(!nextOcurrence){
            pageToErase = i;
            break;
        }
        if(nextOcurrence > distance){
            pageToErase = i;
            distance = nextOcurrence;
        }
    }
    pages.erase(std::find(pages.begin(), pages.end(), pageToErase));
    pages.push_back(page);
    return 0;
}

std::size_t OPTAlgorithm::findNextOcurrence(std::vector<std::size_t> lines, std::size_t index, std::size_t id) {

    // Encontra a proxima ocorrencia de uma pagina
    // Retorna o indice da proxima ocorrencia
    // Se nao houver proxima ocorrencia, retorna -1

    for(std::size_t i = index; i < lines.size(); i++) if(lines[i] == id) return i;
    return 0;
}
