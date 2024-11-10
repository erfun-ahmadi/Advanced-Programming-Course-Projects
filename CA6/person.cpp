#include "person.hpp"

using namespace std;

Person::Person(string _name) {
    member_name = _name;
}

string Person::get_member_name() {
    return member_name;
}

int Person::get_num_of_borrowed_documents() {
    return borrowed_documents.size();
}

string Person::check_borrowed_documents(int num_of_document) {
    return borrowed_documents[num_of_document]->get_document_title();
}

void Person::borrow(Document* borrowed_document, int days_passed) {
    borrowed_documents.push_back(borrowed_document);
    borrowed_documents[borrowed_documents.size()-1]->set_deadline(days_passed);
}

void Person::extend(string document_title, int days_passed) {
    for(int num_of_borrowed = 0; num_of_borrowed < borrowed_documents.size(); num_of_borrowed++) {
        if (borrowed_documents[num_of_borrowed]->get_document_title() == document_title) {
            if (borrowed_documents[num_of_borrowed]->get_days_passed() == days_passed) {
                cout << EXTEND_ON_BORROW_DAY << endl;
                exit(EXIT_SUCCESS);
            }
            else if (borrowed_documents[num_of_borrowed]->get_deadline() < borrowed_documents[num_of_borrowed]->get_days_passed()) {
                cout << EXTEND_AFTER_DEADLINE << endl;
                exit(EXIT_SUCCESS);
            }
            else if (borrowed_documents[num_of_borrowed]->get_num_of_extends() >= EXTEND_CEILING) {
                cout << NO_MORE_EXTENDS << endl;
                exit(EXIT_SUCCESS);
            }
            else {
                borrowed_documents[num_of_borrowed]->extend();
                break;
            }
        }
        else if (num_of_borrowed == borrowed_documents.size()-1) {
            cout << NO_BORROWED_DOCUMENT <<endl;
            exit(EXIT_SUCCESS);
        }
    }
}

void Person::return_borrowed(string document_title, vector <Document*> &documents) {
    for(int num_of_borrowed = 0; num_of_borrowed < borrowed_documents.size(); num_of_borrowed++) {
        if (borrowed_documents[num_of_borrowed]->get_document_title() == document_title) {
            documents.push_back(borrowed_documents[num_of_borrowed]);
            borrowed_documents.erase(borrowed_documents.begin(), borrowed_documents.begin()+num_of_borrowed+1);

        }
        else if (num_of_borrowed == borrowed_documents.size()-1) {
            cout << NO_BORROWED_DOCUMENT << endl;
            exit(EXIT_SUCCESS);
        }
    }
}

void Person::update_days(int days) {
    for (int num_of_borrowed = 0; num_of_borrowed < borrowed_documents.size(); num_of_borrowed++) {
        borrowed_documents[num_of_borrowed]->update_days(days);
    }
}

int Person::calculate_penalty() {
    for (int num_of_borrowed = 0; num_of_borrowed < borrowed_documents.size(); num_of_borrowed++) {
       penalty += borrowed_documents[num_of_borrowed]->calculate_penalty();
    }
    return penalty;
}