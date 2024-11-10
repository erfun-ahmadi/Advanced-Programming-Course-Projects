#ifndef UTAXI_H
#define UTAXI_H

#include "locations.h"
#include "drivers.h"
#include "passengers.h"
#include "trips.h"
#include "const_values.h"
#include "sstream"
#include "algorithm"

class Utaxi {
private:
    std::vector <Location> address;
    std::vector <Trip*> trips;
    std::vector <User*> users;
    std::string second_command;
    std::string seperator;
public:
    void add_locations(char* argv[]);
    void post_command(std::vector <std::string> &commands);
    void get_command(std::vector <std::string> &commands);
    void delete_command(std::vector <std::string> &commands);
    void signup(std::vector <std::string> &commands);
    int set_user_and_role(std::vector <std::string> &commands, std::string &username, std::string &role);
    void check_duplicated_users(std::string _username);
    void aplly_for_trip(std::vector <std::string> &commands);
    int set_user_and_location(std::vector <std::string> &commands, std::string &username, std::string &origin, std::string &destination);
    int find_user(std::string username);
    int find_location(std::string location);
    int find_trip(int id);
    void add_trip_for_passenger(int user_index, std::string origin, std::string destination);
    void show_trips(std::vector <std::string> &commands);
    void show_all_trips(std::vector <std::string> &commands);
    void show_specefic_trip(std::vector <std::string> &commands);
    int set_user_and_id(std::vector <std::string> &commands, std::string &username, int &id);
    void delete_trip(std::vector <std::string> &commands);
    void match_user_and_id(std::string username, int id);
    void accept_trip(std::vector <std::string> &commands);
    void add_trip_for_driver(int user_index, int trip_index);
    void finish_trip(std::vector <std::string> &commands);
    void remove_trip_for_driver(int user_index, int trip_index);
    int find_needed_command(std::vector <std::string> commands, std::string needed_command);
};

#endif