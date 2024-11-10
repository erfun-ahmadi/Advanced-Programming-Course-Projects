#ifndef MAGAZINE_HH
#define MAGAZINE_HH

#include "document.hpp"

class Magazine : public Document {
private:
    int year, number;
public:
    Magazine(std::string _title, int _year, int _number, int _days_passed);
    virtual void extend();
    virtual int calculate_penalty();
};

#endif