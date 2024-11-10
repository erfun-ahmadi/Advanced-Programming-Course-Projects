#include "errors.h"
#include <iostream>

using namespace std;

Error::Error(string _type) {
    error_type = _type;
}

void Error::show_error() {
    cout << error_type << endl;
}