#ifndef _H_PAGE
#define _H_PAGE

#include <iostream>

class Page {

private:

    std::size_t id;
    std::size_t tag;

public:

    Page();
    Page(std::size_t _id);
    Page(const Page &other);
    
    ~Page();

    std::size_t getId() const;
    std::size_t getTag() const;  

    void setTag(std::size_t _tag);  

    friend std::ostream &operator<<(std::ostream& os, const Page& page);

};

#endif
