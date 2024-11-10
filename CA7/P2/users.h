#ifndef USERS_H
#define USERS_H

#include <math.h>
#include "trips.h"
#include "errors.h"
#include "locations.h"

class User {
protected:
    std::string username;
    int trip_id;
public:
    User(std::string _username);
    virtual void apply_for_trip(std::vector <Trip*> &trips, std::string origin, std::string destination, int id,
                                std::string is_in_hurry, double cost) = 0;
    virtual int get_num_of_trips() = 0;
    virtual void show_all_trips(std::vector <Trip*> trips, std::string sorted_by_cost) = 0;
    virtual void show_specefic_trips(std::vector <Trip*> trips, int id) = 0;
    int get_trip_id();
    virtual void delete_trip_application(std::vector <Trip*> trips, int id) = 0;
    virtual void accept_trip(std::vector <Trip*> &trips, int trip_index) = 0;
    virtual void finish_trip(std::vector <Trip*> &trips, int trip_index) = 0;
    virtual double count_price(std::vector <Location*> address, int origin_index, int destination_index, std::string is_in_hurry) = 0;
    std::string get_username();
};

#endif