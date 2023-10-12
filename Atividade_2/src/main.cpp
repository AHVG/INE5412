#include "replacementAlgorithm.h"
#include "simulator.h"



int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <frames>" << std::endl;
        return 1;
    }
    
    std::size_t frames = std::atoi(argv[1]);
    Simulator simulator;
    simulator.run(frames);

    return 0;
}