
#include <vector>


class Context {

private:

    long int SP; //stack pointer
    long int PC; //program counter
    long int status;
    long int gpr[6]; // general purpose registers

public:

    Context(long int _SP, long int _PC, long int _status){
        SP = _SP;
        PC = _PC;
        status = _status;
    };

    ~Context(){};

    long int getSP() const { return SP; };
    long int getPC() const { return PC; };
    long int getStatus() const { return status; };
    long int *getGpr() const { return gpr; };

    void setSP(long int _SP) { SP = _SP; };
    void setPC(long int _PC) { PC = _PC; };
    void setstatus(long int _status) { status = _status; };
    void setGpr(const std::vector<long int>& _gpr) { gpr = _gpr; };

};