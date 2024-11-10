#ifndef REFRENCE_HH
#define REFRENCE_HH

#include "document.hpp"

class Reference : public Document {
public:
    Reference(std::string _title, int _days_passed);
    virtual void extend();
    virtual int calculate_penalty();
};

#endif