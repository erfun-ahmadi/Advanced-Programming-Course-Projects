#ifndef DRIVERS_H
#define DRIVERS_H

#include "users.h"

class Driver : public User {
private:
    std::vector <Trip*> accepted_trip;
public:
    Driver(std::string _username);
    void apply_for_trip(std::vector <Trip*> &trips, std::string origin, std::string destination, int id, 
                        std::string is_in_hurry, double cost);
    int get_num_of_trips();
    std::vector <Trip*> show_all_trips(std::vector <Trip*> trips, std::string sorted_by_cost);
    std::vector <Trip*> show_trips_sorted_by_cost(std::vector <Trip*> trips);
    std::vector <Trip*> show_trips_not_sorted_by_cost(std::vector <Trip*> trips);
    Trip* show_specefic_trips(std::vector <Trip*> trips, int id);
    void delete_trip_application(std::vector <Trip*> trips, int id); 
    void accept_trip(std::vector <Trip*> &trips, int trip_index);
    void finish_trip(std::vector <Trip*> &trips, int trip_index);
    double count_price(std::vector <Location*> address, int origin_index, int destination_index, std::string is_in_hurry);
};

#endif