#ifndef PROFESSOR_HH
#define PROFESSOR_HH

#include "person.hpp"

class Professor : public Person {
private:
    int ceiling_of_borrows = DOCUMENT_CEILING_FOR_PROFESSOR;
public:
    Professor(std::string _name); 
    virtual int get_ceiling_of_borrows();

};

#endif