#ifndef _H_REGISTER
#define _H_REGISTER

#include <iostream>
#include <array>

class Register {

private:

    std::array<unsigned char, 8> bytes;

public:

    Register();
    Register(const std::array<unsigned char, 8> &_bytes);
    ~Register();

    void setBytes(const std::array<unsigned char, 8> &newBytes);
    std::array<unsigned char, 8> getBytes() const;

	friend std::ostream &operator<<(std::ostream& os, const Register& p);

};

#endif