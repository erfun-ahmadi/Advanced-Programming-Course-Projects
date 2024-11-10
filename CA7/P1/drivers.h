#ifndef DRIVERS_H
#define DRIVERS_H

#include "users.h"

class Driver : public User {
private:
    std::vector <Trip*> accepted_trip;
public:
    Driver(std::string _username);
    void apply_for_trip(std::vector <Trip*> &trips, std::string origin, std::string destination, int id);
    int get_num_of_trips();
    void show_all_trips(std::vector <Trip*> trips);
    void show_specefic_trips(std::vector <Trip*> trips, int id);
    void delete_trip_application(std::vector <Trip*> trips, int id); 
    void accept_trip(std::vector <Trip*> &trips, int trip_index);
    void finish_trip(std::vector <Trip*> &trips, int trip_index);
};

#endif