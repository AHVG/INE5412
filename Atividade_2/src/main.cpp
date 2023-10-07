#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>


int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <frames>" << std::endl;
        return 1;
    }

    int frames = std::atoi(argv[1]);
    std::vector<int> referencias;

    std::cout << "Number of RAM frames: " << frames << "\n\n";
    std::cout << "File content (./entradas/entrada.txt): " << "\n\n";
    std::string line;
    int number_of_line = 1;
    while (std::cin >> line) {
        std::cout << std::setw(5) << number_of_line << ": " << line << "\n";
        number_of_line++;
    }

    return 0;
}