#include "student.hpp"

using namespace std;

Student::Student(string _name, string _id) : Person(_name) {
    student_id = _id;
}

int Student::get_ceiling_of_borrows() {
    return ceiling_of_borrows;
}