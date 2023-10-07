
#include "page.h"


Page::Page() : id(0), lastAcess(0) {}


Page::Page(std::size_t _id) : id(_id), lastAcess(0) {}


Page::Page(std::size_t _id, std::size_t _lastAcess) : id(_id), lastAcess(_lastAcess) {}


Page::Page(const Page &other) : Page(other.getId(), other.getLastAcess()) {}


Page::~Page() {}


std::size_t Page::getId() const {
    return id;
}


std::size_t Page::getLastAcess() const {
    return lastAcess;
}


void Page::setLastAcess(std::size_t newLastAcess) {
    lastAcess = newLastAcess;
}


std::ostream &operator<<(std::ostream& os, const Page& page)  {

    os << "Page(std::size_t id = " << page.getId() << ", std::size_t lastAcess = " << page.getLastAcess() << ")"; 

    return os;
}