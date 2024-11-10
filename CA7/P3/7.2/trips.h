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
    double cost;
    std::string is_in_hurry;
public:
    Trip(std::string _uername, std::string _origin, std::string _destination, int _id, std::string _is_in_hurry, double _cost);
    int get_id();
    std::string get_username();
    std::string get_origin();
    std::string get_destination();
    std::string get_status();
    void change_availability();
    int get_availability();
    void change_status(std::string new_status);
    double get_cost();
};

#endif