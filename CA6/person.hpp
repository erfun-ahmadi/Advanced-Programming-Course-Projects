#ifndef PERSON_HH
#define PERSON_HH

#include "document.hpp"

class Person {
protected:
    std::string member_name;
    int num_of_borrowed_doucuments = 0;
    int num_of_extend = 0;
    int penalty = 0;
    std::vector <Document*> borrowed_documents;
public:
    Person(std::string _name); 
    int get_num_of_borrowed_documents();
    std::string check_borrowed_documents(int num_of_document);  
    std::string get_member_name();
    virtual int get_ceiling_of_borrows() = 0;
    void borrow(Document* borrowed_document, int days_passed);
    void extend(std::string document_title, int days_passed);
    void return_borrowed(std::string document_title, std::vector <Document*> &documents);
    void update_days(int days);
    int calculate_penalty();
};

#endif