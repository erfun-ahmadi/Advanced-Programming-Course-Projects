#ifndef PASSENGERS_H
#define PASSENGERS_H

#include "users.h"

class Passenger : public User {
private:
    std::vector <Trip*> passenger_trip;
public:
    Passenger(std::string _username);
    void apply_for_trip(std::vector <Trip*> &trips, std::string origin, std::string destination, int id, 
                        std::string is_in_hurry, double cost);
    int get_num_of_trips();
    void show_all_trips(std::vector <Trip*> trips, std::string sorted_by_cost);
    void show_specefic_trips(std::vector <Trip*> trips, int id);
    void delete_trip_application(std::vector <Trip*> trips, int id);
    void accept_trip(std::vector <Trip*> &trips, int trip_index);
    void finish_trip(std::vector <Trip*> &trips, int trip_index);
    double count_price(std::vector <Location*> address, int origin_index, int destination_index, std::string is_in_hurry);
};

#endif