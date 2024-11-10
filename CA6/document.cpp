#include "document.hpp"

using namespace std;

Document::Document(string _title, int _days_passed) {
    document_title = _title;
    borrow_day = _days_passed;
    days_passed = borrow_day;
}

string Document::get_document_title() {
    return document_title;
}

void Document::set_deadline(int _days_passed) {
    borrow_day = _days_passed;
    return_deadline = borrow_day+DEADLINE_AFTER_BORROW;
}

int Document::get_days_passed() {
    return borrow_day;
}

int Document::get_deadline() {
    return return_deadline;
}

int Document::get_num_of_extends() {
    return num_of_extends;
}

void Document::update_days(int days) {
    days_passed += days;
}