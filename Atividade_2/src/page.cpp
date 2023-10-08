
#include "page.h"
#include <vector>
#include <algorithm>

Page::Page() : id(0) {}


Page::Page(std::size_t _id) : id(_id) {}

Page::Page(const Page &other) : Page(other.getId()) {}


Page::~Page() {}

std::size_t Page::getId() const {
    return id;
}

std::size_t Page::getTag() const {
    return tag;
}

void Page::setTag(std::size_t _tag) {
    tag = _tag;
}

std::ostream &operator<<(std::ostream& os, const Page& page)  {

    os << "Page(std::size_t id = " << page.getId() << ")"; 

    return os;
}