#ifndef ERRORS_H
#define ERRORS_H

#include <string>

class Error {
private:
    std::string error_type;
public:
    Error(std::string _type);
    void show_error();
};

#endif 