#include "book.hpp"

using namespace std;

Book::Book(string _title, int _days_passed) : Document(_title, _days_passed) {}

void Book::extend() {
    return_deadline += 10;
    num_of_extends += 1;
}

int Book::calculate_penalty() {
    if (days_passed-return_deadline <= 0) {
        delay_penalty = 0;
    }
    else if (days_passed-return_deadline <= BOOK_LOW_DAYS_PASSED) {
        for (int days_passed_deadline = 1; days_passed_deadline <= days_passed-return_deadline; days_passed_deadline++) {
            delay_penalty += BOOK_LOW_DAYS_PENALTY;
        }
    }
    else if (days_passed-return_deadline <= BOOK_MEDIUM_DAYS_PASSED){
        for (int days_passed_deadline = 1; days_passed_deadline <= BOOK_LOW_DAYS_PASSED; days_passed_deadline++) {
            delay_penalty += BOOK_LOW_DAYS_PENALTY;
        }
        for (int days_passed_deadline = BOOK_LOW_DAYS_PASSED+1; days_passed_deadline <= days_passed-return_deadline;
             days_passed_deadline++) {
            delay_penalty += BOOK_MEDIUM_DAYS_PENALTY;        
        }
    }
    else {
        for (int days_passed_deadline = 1; days_passed_deadline <= BOOK_LOW_DAYS_PASSED; days_passed_deadline++) {
            delay_penalty += BOOK_LOW_DAYS_PENALTY;
        }
        for (int days_passed_deadline = BOOK_LOW_DAYS_PASSED+1; days_passed_deadline <= BOOK_MEDIUM_DAYS_PASSED;
             days_passed_deadline++) {
            delay_penalty += BOOK_MEDIUM_DAYS_PENALTY;        
        }
        for (int days_passed_deadline = BOOK_MEDIUM_DAYS_PASSED+1; days_passed_deadline <= days_passed-return_deadline;
             days_passed_deadline++) {
            delay_penalty += BOOK_MUCH_DAYS_PENALTY;        
        }
    }
    return delay_penalty;
}