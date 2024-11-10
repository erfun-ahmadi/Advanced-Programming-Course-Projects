#include "magazine.hpp"

using namespace std;

Magazine::Magazine(string _title, int _year, int _number, int _days_passed) : Document(_title, _days_passed) {
    year = _year;
    number = _number;
}

void Magazine::extend() {
    cout << MAGAZINE_EXTEND_WARNING << endl;
    exit(EXIT_SUCCESS);
}

int Magazine::calculate_penalty() {
    if (days_passed-return_deadline <= 0) {
        delay_penalty = 0;
    }
    else {
        for (int days_passed_deadline = 1; days_passed_deadline <= days_passed-return_deadline; days_passed_deadline++) {
            if (year < MAGAZINE_PUBLISH_YEAR) {
                delay_penalty += MAGAZINE_PENALTY_BEFORE_1390;
            }
            else {
                delay_penalty += MAGAZINE_PENALTY_AFTER_1390;
            }
        }
    }
    return delay_penalty;
}