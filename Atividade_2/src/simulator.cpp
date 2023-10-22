#include "simulator.h"
#include "replacementAlgorithm.h"
#include <cstdio>
#include <vector>
#include <thread>
#include <future>

void Simulator::run(std::size_t frames) {
    std::vector<std::size_t> lines;
    std::size_t line;

    while (scanf("%zu", &line) != EOF) lines.push_back(line);

    FIFOAlgorithm fifo(frames, lines);
    LRUAlgorithm lru(frames, lines);
    OPTAlgorithm opt(frames, lines);

    auto execute = [](ReplacementAlgorithm& algo) {
        return algo.simulate();
    };

    auto futureFIFO = std::async(execute, std::ref(fifo));
    auto futureLRU = std::async(execute, std::ref(lru));
    auto futureOPT = std::async(execute, std::ref(opt));

    std::size_t pfsFIFO = futureFIFO.get();
    std::size_t pfsLRU = futureLRU.get();
    std::size_t pfsOPT = futureOPT.get();

    printf("%lu quadros\n", frames);
    printf("%lu refs\n", lines.size());
    printf("FIFO: %lu PFs\n", pfsFIFO);
    printf("LRU: %lu PFs\n", pfsLRU);
    printf("OPT: %lu PFs\n", pfsOPT);

}   
