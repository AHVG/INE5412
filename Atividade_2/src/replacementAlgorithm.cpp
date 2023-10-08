
#include "replacementAlgorithm.h"

#include <algorithm>

ReplacementAlgorithm::ReplacementAlgorithm() : RAMFrames(0) {}


ReplacementAlgorithm::ReplacementAlgorithm(std::size_t _RAMFrames) : RAMFrames(_RAMFrames) {}


ReplacementAlgorithm::~ReplacementAlgorithm() {}


std::vector<Page> ReplacementAlgorithm::getPages() const {
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

    auto it = std::find_if(pages.begin(), pages.end(), [page] (const Page &p) {
        return p.getId() == page;
    });

    if (it == pages.end()) {
        if (full()) {
            pages.erase(pages.begin());
        }
        Page aux(page);
        pages.push_back(aux);
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
 
    auto it = std::find_if(pages.begin(), pages.end(), [page] (const Page &p) {
        return p.getId() == page;
    });

    if (it == pages.end()) {
        if (full()) {
            pages.erase(pages.begin());
        }
        Page aux(page);
        pages.push_back(aux);
        return 0;
    }
    
    Page aux(*it);
    pages.erase(it);
    pages.push_back(aux);

    return 1;
}


OPTAlgorithm::OPTAlgorithm(std::size_t _RAMFrames) : ReplacementAlgorithm(_RAMFrames) {}
OPTAlgorithm::OPTAlgorithm() : ReplacementAlgorithm() {}  

OPTAlgorithm::~OPTAlgorithm() {}


int OPTAlgorithm::accessMemory(std::size_t page) {

    // OPT: Optimal
    // Caso page fault, retira o elemento que vai demorar mais para ser acessado e insere o novo elemento no final da lista
    // Ou seja, o elemento com maior tag
    // Caso ele acessar uma pagina que ja estava na lista, nao faz nada

    auto it = std::find_if(pages.begin(), pages.end(), [page] (const Page &p) {
        return p.getId() == page;
    });

    if (it == pages.end()) {
        if (full()) {
            pages.erase(pages.begin() + getPageWithMaxTag());
        }
        Page aux(page);
        pages.push_back(aux);
        return 0;
    }
    return 1;
}

void OPTAlgorithm::refreshTags(std::vector<std::size_t> lines ,std::size_t index) {

    // Atualiza as tags das paginas que estao na lista de paginas a partir do indice que deu page fault
    // A tag eh a distancia que a pagina vai ser acessada novamente
    // Se a pagina nao for acessada novamente, a tag eh 0

    for(std::size_t i = 0; i < pages.size(); i++){
        std::size_t currentId = pages[i].getId();
        std::size_t nextOcurrence = findNextOcurrence(lines, index, currentId);
        if(nextOcurrence == 0){
            pages[i].setTag(0);
        } else {
            pages[i].setTag(nextOcurrence - index);
        }
    }
}

std::size_t OPTAlgorithm::findNextOcurrence(std::vector<std::size_t> lines, std::size_t index, std::size_t id) {

    // Encontra a proxima ocorrencia de uma pagina
    // Retorna o indice da proxima ocorrencia
    // Se nao houver proxima ocorrencia, retorna -1

    for(std::size_t i = index; i < lines.size(); i++){
        if(lines[i] == id){
            return i;
        }
    }
    return 0;
}

std::size_t OPTAlgorithm::getPageWithMaxTag(){

    // Encontra a pagina que vai demorar mais para ser acessada
    // Retorna o indice dessa pagina
    
    std::size_t maxTag = 0;
    std::size_t index = 0;
    for(std::size_t i = 0; i < pages.size(); i++){
        if(pages[i].getTag() == 0){
            return i;
        }
        if(pages[i].getTag() > maxTag){
            maxTag = pages[i].getTag();
            index = i;
        }
    }
    return index;
}