#include "errors.h"
#include <iostream>

using namespace std;

Error::Error(string _type) {
    error_type = _type;
}

string Error::get_error() {
    return error_type;
}