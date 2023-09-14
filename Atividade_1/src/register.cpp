
#include "register.h"

Register::Register() {
    for (auto &byte : bytes) byte = 0xff;
}
Register::~Register() {}

void Register::setBytes(const std::array<unsigned char, 8> &newBytes) {
    bytes = newBytes;
}


std::array<unsigned char, 8> Register::getBytes() const {
    return bytes;
}