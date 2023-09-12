
#include <iostream>

#include "utils.h"

// Utils onde ficam as funções auxiliares para que printamos o cout com cores
void customCout(std::string text, std::string color) {
    setColor(color);
    std::cout << text;
    resetColor();
}

void setColor(std::string color) {
    std::cout << color;
}

void resetColor() {
    std::cout << RESET_COLOR;
}