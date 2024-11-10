#include "professor.hpp"

using namespace std;

Professor::Professor(string _name) : Person(_name) {}

int Professor::get_ceiling_of_borrows() {
    return ceiling_of_borrows;
}