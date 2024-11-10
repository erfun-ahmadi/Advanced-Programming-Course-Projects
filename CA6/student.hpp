#ifndef STUDENT_HH
#define STUDENT_HH

#include "person.hpp"

class Student : public Person {
private:
    std::string student_id;
    int ceiling_of_borrows = DOCUMENT_CEILING_FOR_STUDENT;
public:
    Student(std::string _name, std::string _id); 
    virtual int get_ceiling_of_borrows();
};

#endif