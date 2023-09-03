#include <vector>
class Context{
    private:
    long int SP; //stack pointer
    long int PC; //program counter
    long int status;
    std::vector<long int> gpp; // general purpose registers
    public:
    Context(long int _SP, long int _PC, long int _status, const std::vector<long int>& _gpp){
        SP = _SP;
        PC = _PC;
        status = _status;
        gpp = _gpp;
    };
    ~Context(){};
    long int get_SP(){ return SP;};
    long int get_PC(){ return PC;};
    long int get_status(){ return status;};
    std::vector<long int> get_gpp(){ return gpp;};

    void set_SP(long int _SP){ SP = _SP;};
    void set_PC(long int _PC){ PC = _PC;};
    void set_status(long int _status){ status = _status;};
    void set_gpp(const std::vector<long int>& _gpp){ gpp = _gpp;};



};