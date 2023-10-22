
#include "replacementAlgorithm.h"

#include <algorithm>

ReplacementAlgorithm::ReplacementAlgorithm(std::size_t _RAMFrames, std::vector<std::size_t> &_lines) : RAMFrames(_RAMFrames), lines(_lines) {}


ReplacementAlgorithm::~ReplacementAlgorithm() {}

std::vector<std::size_t>::iterator ReplacementAlgorithm::containsPage(std::size_t page) {
    return std::find_if(pages.begin(), pages.end(), [page] (const std::size_t &p) {
        return p == page;
    });
}

FIFOAlgorithm::FIFOAlgorithm(std::size_t _RAMFrames, std::vector<std::size_t> &_lines) : ReplacementAlgorithm(_RAMFrames, _lines) {}

FIFOAlgorithm::~FIFOAlgorithm() {}


// int FIFOAlgorithm::accessMemory(std::size_t page) {

//     // FIFO: First In First Out
//     // Caso page fault, retira o primeiro elemento da lista e insere o novo elemento no final da lista
//     // Caso ele acessar uma pagina que ja estava na lista, nao faz nada

//     if (containsPage(page) == pages.end()) {
//         if(pages.size() == RAMFrames) pages.erase(pages.begin());
//         pages.push_back(page);
//         return 0;
//     }

//     return 1;
// }


std::size_t FIFOAlgorithm::simulate(){

    // LRU: Least Recently Used
    // Caso page fault, retira o ultimo elemento da lista e insere o novo elemento no inicio da lista
    // Caso ele acessar uma pagina que ja estava na lista, joga esse elemento para o inicio da lista
    
    std::size_t pfs = 0;
    for (std::size_t page : lines){
        if (containsPage(page) == pages.end()) {
            if(pages.size() == RAMFrames) pages.erase(pages.begin());
            pages.push_back(page);
            pfs++;
        }

    }
    return pfs;
}

LRUAlgorithm::LRUAlgorithm(std::size_t _RAMFrames, std::vector<std::size_t> &_lines) : ReplacementAlgorithm(_RAMFrames, _lines) {}

LRUAlgorithm::~LRUAlgorithm() {}

// int LRUAlgorithm::accessMemory(std::size_t page) {

//     // LRU: Least Recently Used
//     // Caso page fault, retira o ultimo elemento da lista e insere o novo elemento no inicio da lista
//     // Caso ele acessar uma pagina que ja estava na lista, joga esse elemento para o inicio da lista

//     auto it = containsPage(page);
//     if (it == pages.end()) {
//         if(pages.size() == RAMFrames) pages.erase(pages.begin());
//         pages.push_back(page);
//         return 0;
//     }
//     pages.erase(it);
//     pages.push_back(page);

//     return 1;
// }

std::size_t LRUAlgorithm::simulate(){

    // LRU: Least Recently Used
    // Caso page fault, retira o ultimo elemento da lista e insere o novo elemento no inicio da lista
    // Caso ele acessar uma pagina que ja estava na lista, joga esse elemento para o inicio da lista
    
    std::size_t pfs = 0;
    for (std::size_t page : lines){
        auto it = containsPage(page);
        if (it == pages.end()) {
            if(pages.size() == RAMFrames) pages.erase(pages.begin());
            pages.push_back(page);
            pfs++;
        }
        else{
            pages.erase(it);
            pages.push_back(page);
        }

    }
    return pfs;
}


OPTAlgorithm::OPTAlgorithm(std::size_t _RAMFrames, std::vector<std::size_t> &_lines) : ReplacementAlgorithm(_RAMFrames, _lines), currentLine(-1)  {entrySize = lines.size();}

OPTAlgorithm::~OPTAlgorithm() {}

// int OPTAlgorithm::accessMemory(std::size_t page) {

//     // OPT: Optimal
//     // Caso page fault, retira o elemento que vai demorar mais para ser acessado e insere o novo elemento no final da lista
//     // Ou seja, o elemento com maior tag
//     // Caso ele acessar uma pagina que ja estava na lista, nao faz nada

//     currentLine++;

//     if(containsPage(page) != pages.end()) return 1;

//     if(pages.size() != RAMFrames) {
//         pages.push_back(page);
//         return 0;
//     }

//     std::size_t pageToErase = 0;
//     std::size_t distance = 0;
    
//     for(std::size_t i : pages){
//         std::size_t nextOcurrence = findNextOcurrence(currentLine, i);
//         if(!nextOcurrence){
//             pageToErase = i;
//             break;
//         }
//         if(nextOcurrence > distance){
//             pageToErase = i;
//             distance = nextOcurrence;
//         }
//     }
//     pages.erase(std::find(pages.begin(), pages.end(), pageToErase));
//     pages.push_back(page);
//     return 0;
// }

std::size_t OPTAlgorithm::simulate(){

    // OPT: Optimal
    // Caso page fault, retira o elemento que vai demorar mais para ser acessado e insere o novo elemento no final da lista
    // Ou seja, o elemento com maior tag
    // Caso ele acessar uma pagina que ja estava na lista, nao faz nada
    
    std::size_t pfs = 0;
    for (std::size_t page : lines){
        currentLine++;
        if(containsPage(page) != pages.end()) continue;

        pfs++;
        if(pages.size() != RAMFrames) {
            pages.push_back(page);
            continue;
        }

        std::size_t pageToErase = 0;
        std::size_t distance = 0;
        
        for(std::size_t i : pages){
            std::size_t nextOcurrence = findNextOcurrence(currentLine, i);
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
    }
    return pfs;
}

std::size_t OPTAlgorithm::findNextOcurrence(std::size_t index, std::size_t id) {

    // Encontra a proxima ocorrencia de uma pagina
    // Retorna o indice da proxima ocorrencia
    // Se nao houver proxima ocorrencia, retorna 0

    for(std::size_t i = index; i < entrySize; i++) if(lines[i] == id) return i;
    return 0;
}
