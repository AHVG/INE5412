#ifndef _H_REGISTER
#define _H_REGISTER

#include <array>

class Register {

private:

    std::array<unsigned char, 8> bytes;

public:

    Register();
    ~Register();

    void setBytes(const std::array<unsigned char, 8> &newBytes);
    std::array<unsigned char, 8> getBytes() const;

};

#endif