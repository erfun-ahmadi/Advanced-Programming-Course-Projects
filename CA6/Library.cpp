#include <iostream>
#include "Library.hpp"

using namespace std;

void Library::add_student_member(string student_id, string student_name) {
    if (members.size() == 0) {
        if (student_name == "" || student_id == "") {
            cout << EMPTY_FIELD_ERROR << endl;
            exit(EXIT_SUCCESS);
        }
        else {
            Student *std = new Student(student_name, student_id);
            members.push_back(std);
        }    
    }
    else {
        for (int num_of_member = 0; num_of_member < members.size(); num_of_member++) {
            if (student_name == members[num_of_member]->get_member_name()) {
                cout << SAME_NAME_ERROR << endl;
                exit(EXIT_SUCCESS);
            }
            else if (student_name == "" || student_id == "") {
                cout << EMPTY_FIELD_ERROR << endl;
                exit(EXIT_SUCCESS);
            }
            else if (num_of_member == members.size()-1) {
                Student *std = new Student(student_name, student_id);
                members.push_back(std);
                break;
            }
        }        
    }
}


void Library::add_prof_member(string prof_name) {
    if (members.size() == 0) {
        if (prof_name == "") {
            cout << EMPTY_FIELD_ERROR << endl;
            exit(EXIT_SUCCESS);
        }
        else {
            Professor *prof = new Professor(prof_name);
            members.push_back(prof);
        } 
    }
    else {
        for (int num_of_member = 0; num_of_member < members.size(); num_of_member++) {
            if (prof_name == members[num_of_member]->get_member_name()) {
                cout << SAME_NAME_ERROR << endl;
                exit(EXIT_SUCCESS);
            }
            else if (prof_name == "") {
                cout << EMPTY_FIELD_ERROR << endl;
                exit(EXIT_SUCCESS);
            }
            else if (num_of_member == members.size()-1) {
                Professor *prof = new Professor(prof_name);
                members.push_back(prof);
                break;
            }
        }        
    }
}


void Library::add_book(string book_title, int copies) {
    if (documents.size() == 0) {
        if (book_title == "") {
            cout << EMPTY_FIELD_ERROR << endl;
            exit(EXIT_SUCCESS);
        }
        else {
            for (int num_of_copies = 0; num_of_copies < copies; num_of_copies++) {
                Book *book = new Book(book_title, days_passed);
                documents.push_back(book);
            }
        }
    }
    else {
        for (int num_of_document = 0; num_of_document < documents.size(); num_of_document++) {
            if (book_title == documents[num_of_document]->get_document_title()) {
                cout << SAME_DOCUMENT_TITLE << endl;
                exit(EXIT_SUCCESS);
            }
            else if (book_title == "") {
                cout << EMPTY_FIELD_ERROR << endl;
                exit(EXIT_SUCCESS);
            }
            else if (num_of_document == documents.size()-1) {
                for (int num_of_copies = 0; num_of_copies < copies; num_of_copies++) {
                    Book *book = new Book(book_title, days_passed);
                    documents.push_back(book);
                } 
                break;          
            }
        }
    }
}


void Library::add_magazine(string magazine_title, int year, int number, int copies) {
    if (documents.size() == 0) {
        if (magazine_title == "") {
            cout << EMPTY_FIELD_ERROR << endl;
            exit(EXIT_SUCCESS);
        }
        else {
            for (int num_of_copies = 0; num_of_copies < copies; num_of_copies++) {
                Magazine *mag = new Magazine(magazine_title, year, number, days_passed);
                documents.push_back(mag);
            }
        }
    }
    else {
        for (int num_of_document = 0; num_of_document < documents.size(); num_of_document++) {
            if (magazine_title == documents[num_of_document]->get_document_title()) {
                cout << SAME_DOCUMENT_TITLE << endl;
                exit(EXIT_SUCCESS);
            }
            else if (magazine_title == "") {
                cout << EMPTY_FIELD_ERROR << endl;
                exit(EXIT_SUCCESS);
            }
            else if (year <= 0) {
                cout << INVALID_YEAR << endl;
                exit(EXIT_SUCCESS);
            }
            else if (number <= 0) {
                cout << INVALID_NUMBER << endl;
                exit(EXIT_SUCCESS);
            }
            else if (num_of_document == documents.size()-1) {
                for (int num_of_copies = 0; num_of_copies < copies; num_of_copies++) {
                    Magazine *mag = new Magazine(magazine_title, year, number, days_passed);
                    documents.push_back(mag);   
                }
                break;   
            }
        }
    }
}


void Library::add_reference(string reference_title, int copies) {
    if (documents.size() == 0) {
        if (reference_title == "") {
            cout << EMPTY_FIELD_ERROR << endl;
            exit(EXIT_SUCCESS);
        }
        else {
            for (int num_of_copies = 0; num_of_copies < copies; num_of_copies++) {
                Reference *ref = new Reference(reference_title, days_passed);
                documents.push_back(ref);
            }
        }
    }
    else {
        for (int num_of_document = 0; num_of_document < documents.size(); num_of_document++) {
            if (reference_title == documents[num_of_document]->get_document_title()) {
                cout << SAME_DOCUMENT_TITLE << endl;
                exit(EXIT_SUCCESS);
            }
            else if (reference_title == "") {
                cout << EMPTY_FIELD_ERROR << endl;
                exit(EXIT_SUCCESS);
            }
            else if (num_of_document == documents.size()-1) {
                for (int num_of_copies = 0; num_of_copies < copies; num_of_copies++) {
                    Reference *ref = new Reference(reference_title, days_passed);
                    documents.push_back(ref); 
                }  
                break;         
            }
        }
    }
}

void Library::borrow(string member_name, string document_title) {
    for (int num_of_member = 0; num_of_member < members.size(); num_of_member++) {
        if (member_name == members[num_of_member]->get_member_name()) {
            if (members[num_of_member]->get_num_of_borrowed_documents() == 0) {
                check_documents_to_borrow(num_of_member, document_title);
            }
            else {
                for (int num_of_borrowed = 0; num_of_borrowed < members[num_of_member]->get_num_of_borrowed_documents(); num_of_borrowed++) {
                    if (members[num_of_member]->check_borrowed_documents(num_of_borrowed) == document_title) {
                        cout << BORROW_BORROWED_DOCUMENT << endl;
                        exit(EXIT_SUCCESS);
                    }
                    else if (members[num_of_member]->get_num_of_borrowed_documents() == members[num_of_member]->get_ceiling_of_borrows()) {
                        cout << MAX_BORROWED_DOCUMENTS_ERROR << endl;
                        exit(EXIT_SUCCESS);
                    }
                    else if (num_of_borrowed == members[num_of_member]->get_num_of_borrowed_documents()-1) {
                        check_documents_to_borrow(num_of_member, document_title);
                        break;
                    }
                }
            }
        }
    }
}

void Library::check_documents_to_borrow(int num_of_member, string document_title) {
    if (documents.size() == 0) {
        cout << NO_EXISTING_DOCUMENT << endl;
            exit(EXIT_SUCCESS);
    }
    else {
        for (int num_of_document = 0; num_of_document < documents.size(); num_of_document++) {
            if (document_title == documents[num_of_document]->get_document_title()) {
                members[num_of_member]->borrow(documents[num_of_document], days_passed);
                documents.erase(documents.begin()+num_of_document, documents.begin()+num_of_document+1);
                break;
            }
            else if (num_of_document == documents.size()-1) {
                cout << NO_EXISTING_DOCUMENT << endl;
                exit(EXIT_SUCCESS);
            }
        }
    }
}

void Library::extend(string member_name, string document_title) {
    for (int num_of_member = 0; num_of_member < members.size(); num_of_member++) {
        if (members[num_of_member]->get_member_name() == member_name) {
            if (members[num_of_member]->get_num_of_borrowed_documents() == 0) {
                cout << NO_BORROWED_DOCUMENT << endl;
                exit(EXIT_SUCCESS);
            }
            else {
                members[num_of_member]->extend(document_title, days_passed);
            }
        }
    }
}

void Library::return_document(string member_name, string document_title) {
    for (int num_of_member = 0; num_of_member < members.size(); num_of_member++) {
        if (members[num_of_member]->get_member_name() == member_name) {
            if (members[num_of_member]->get_num_of_borrowed_documents() == 0) {
                cout << NO_BORROWED_DOCUMENT << endl;
                exit(EXIT_SUCCESS);
            }
            else {
                members[num_of_member]->return_borrowed(document_title, documents);
            }
        }
    }
}

int Library::get_total_penalty(string member_name) {
    int penalty = 0;
    for (int num_of_member = 0; num_of_member < members.size(); num_of_member++) {
        if (members[num_of_member]->get_member_name() == member_name) {
            penalty += members[num_of_member]->calculate_penalty();
        }
    }
    return penalty;
}

vector <string> Library::available_titles(){
    vector <string> available_titles;
    for (int num_of_documents = 0; num_of_documents < documents.size(); num_of_documents++) {
        available_titles.push_back(documents[num_of_documents]->get_document_title());
    }
    return available_titles;
}

void Library::time_pass(int days) {
    days_passed += days;
    for (int num_of_document = 0; num_of_document < documents.size(); num_of_document++) {
        documents[num_of_document]->update_days(days);
    }
    for (int num_of_member = 0; num_of_member < members.size(); num_of_member++) {
        members[num_of_member]->update_days(days);
    }
}