#ifndef _H_CONTEXT
#define _H_CONTEXT

#include <vector>


class Context {

private:

    long int SP;        // stack pointer
    long int PC;        // program counter
    long int status;
    long int gpr[6];    // general purpose registers

public:

    Context(long int _SP, long int _PC, long int _status);

    ~Context();

    long int getSP() const;
    long int getPC() const;
    long int getStatus() const;
    const long int *getGpr() const;

    void setSP(long int _SP);
    void setPC(long int _PC);
    void setStatus(long int _status);

};

#endif