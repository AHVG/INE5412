#ifndef _H_PAGE
#define _H_PAGE

#include <iostream>

class Page {

    std::size_t id;
    std::size_t lastAcess;

public:

    Page();
    Page(std::size_t _id);
    Page(std::size_t _id, std::size_t _lastAcess);
    Page(const Page &other);
    
    ~Page();

    std::size_t getId() const;
    std::size_t getLastAcess() const;

    void setLastAcess(std::size_t newLastAcess);

    friend std::ostream &operator<<(std::ostream& os, const Page& page);

};

#endif
