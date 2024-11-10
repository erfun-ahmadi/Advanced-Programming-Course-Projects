#ifndef TRIPS_H
#define TRIPS_H

#include <vector>
#include <string>
#include "const_values.h"

class Trip {
private:
    std::string username;
    std::string status = WAITING_STATUS;
    std::string origin;
    std::string destination;
    int trip_id;
    int is_available = YES;
public:
    Trip(std::string _uername, std::string _origin, std::string _destination, int _id);
    void show_trip();
    int get_id();
    std::string get_status();
    void change_availability();
    int get_availability();
    void change_status(std::string new_status);
};

#endif