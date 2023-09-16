
#include "register.h"

// Classe que representa um registrador
Register::Register() {
    for (auto &byte : bytes) byte = 0xff;
}

Register::Register(const std::array<unsigned char, 8> &_bytes) {
    bytes = _bytes;
}

Register::~Register() {}

void Register::setBytes(const std::array<unsigned char, 8> &newBytes) {
    bytes = newBytes;
}

std::array<unsigned char, 8> Register::getBytes() const {
    return bytes;
}

std::ostream &operator<<(std::ostream& os, const Register& p) {
    os << "Registrador: ";
    for (auto byte : p.getBytes()) os << (short int) byte << " ";
    return os;
}