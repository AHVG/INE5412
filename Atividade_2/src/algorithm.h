#ifndef _H_ALGORITHM
#define _H_ALGORITHM

#include <iostream>

class Algorithm {

public:

    Algorithm();
    
    virtual ~Algorithm();

    virtual int accessMemory(std::size_t page) = 0;

};

#endif