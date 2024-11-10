#ifndef DOCUMENT_HH
#define DOCUMENT_HH

#include <iostream>
#include <string>
#include <vector>
#include "const_values.hpp"

class Document {
protected:
    std::string document_title;
    int borrow_day;
    int days_passed;
    int return_deadline;
    int num_of_extends = 0;
    int delay_penalty = 0;
public:
    Document(std::string _title, int _days_passed);
    std::string get_document_title();
    virtual void extend() = 0;
    void set_deadline(int _days_passed);
    int get_days_passed();
    int get_deadline();
    int get_num_of_extends();
    void update_days(int days);
    virtual int calculate_penalty() = 0;
};

#endif