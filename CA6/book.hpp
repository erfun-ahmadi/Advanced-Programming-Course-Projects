#ifndef BOOK_HH
#define BOOK_HH

#include "document.hpp"

class Book : public Document {
public:
    Book(std::string _title, int _days_passed);
    virtual void extend();
    virtual int calculate_penalty();
};

#endif