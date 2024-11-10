#ifndef UTAXI_H
#define UTAXI_H

#include <math.h>
#include "locations.h"
#include "drivers.h"
#include "passengers.h"
#include "trips.h"
#include "const_values.h"
#include "sstream"
#include "algorithm"

class Utaxi {
private:
    std::vector <Location*> address;
    std::vector <Trip*> trips;
    std::vector <User*> users;
    std::string second_command;
    std::string seperator;
public:
    void add_locations(char* argv[]);
    void signup(std::vector <std::string> &commands);
    void check_duplicated_users(std::string _username);
    int aplly_for_trip(std::vector <std::string> &commands);
    int find_user(std::string username);
    int find_location(std::string location);
    void add_trip_for_passenger(int user_index, std::string origin, std::string destination, std::string is_in_hurry, double cost);
    std::vector <Trip*> show_all_trips(std::vector <std::string> &commands);
    Trip* show_specefic_trip(std::vector <std::string> &commands);
    void delete_trip(std::vector <std::string> &commands);
    void match_user_and_id(std::string username, int id);
    void accept_trip(std::vector <std::string> &commands);
    void finish_trip(std::vector <std::string> &commands);
    double get_price(std::vector <std::string> &commands);
    double count_price(int origin_index, int destination_index, std::string is_in_hurry);
};

#endif