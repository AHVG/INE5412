#ifndef _H_CONTEXT
#define _H_CONTEXT

#include <array>
#include "register.h"

class Context {

private:

    Register SP;        // stack pointer
    Register PC;        // program counter
    Register status;
    std::array<Register, 6> gpr;    // general purpose registers

public:

    Context(Register _SP, Register _PC, Register _status);
    Context();

    ~Context();

    Register getSP() const;
    Register getPC() const;
    Register getStatus() const;
    Register getGpr(int index) const;

    void setSP(Register _SP);
    void setPC(Register _PC);
    void setStatus(Register _status);
    void setGpr(int index, Register value);

};

#endif