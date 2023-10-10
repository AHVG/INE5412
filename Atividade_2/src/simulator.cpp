#include "simulator.h"
#include "replacementAlgorithm.h"
#include <cstdio>
#include <vector>
#include <chrono>

void Simulator::run(std::size_t frames) {
    auto start_time = std::chrono::high_resolution_clock::now();
    std::size_t pfsFIFO = 0;
    std::size_t pfsLRU = 0;
    std::size_t pfsOPT = 0;

    char line[256];

    FIFOAlgorithm fifo(frames);
    LRUAlgorithm lru(frames);
    OPTAlgorithm opt(frames);
    
    std::vector<std::size_t> lines;

    while (scanf("%s", line) != EOF) {
        lines.push_back(static_cast<size_t>(std::stoi(line)));
    }

    for (std::size_t i = 0; i < lines.size(); i++){
        std::size_t pageId = lines[i];
        pfsFIFO += !fifo.accessMemory(pageId);
        pfsLRU += !lru.accessMemory(pageId);
        if (opt.full() && !opt.in(pageId))
            //TODO: se a lista estiver cheia e o elemento que eu quiser inserir ja esta na lista, ele nao precisaria chamar o refreshTags
            opt.refreshTags(lines, i);
        pfsOPT += !opt.accessMemory(pageId);
    }


    // Mudar para map o pfs?
    printf("%lu quadros\n", frames);
    printf("%lu refs\n", lines.size());
    printf("FIFO: %lu PFs\n", pfsFIFO);
    printf("LRU: %lu PFs\n", pfsLRU);
    printf("OPT: %lu PFs\n", pfsOPT);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end_time - start_time;
    printf("Tempo de execução: %f segundos\n", duration.count());
}   
