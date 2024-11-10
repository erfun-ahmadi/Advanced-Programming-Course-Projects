#include "utaxi.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

void Utaxi::add_locations(char* argv[]) {
    string each_location;
    ifstream location_file(argv[1]);
    getline(location_file, each_location);
    while (getline(location_file, each_location)) {
        string name;
        float latitude, longitude;
        int traffic_ratio;
        size_t index = each_location.find(',');
        name = each_location.substr(0, index);
        each_location = each_location.substr(index + 1);
        index = each_location.find(',');
        latitude = stod(each_location.substr(0, index));
        each_location = each_location.substr(index + 1);
        index = each_location.find(',');
        longitude = stod(each_location.substr(0, index));
        each_location = each_location.substr(index + 1);
        traffic_ratio = stoi(each_location);
        Location *loc = new Location(name, latitude, longitude, traffic_ratio);
        address.push_back(loc);
    }
    location_file.close();
}

void Utaxi::signup(vector <string> &commands) {  
    if (commands.size() == 2) {          
        check_duplicated_users(commands[0]);
        if (commands[1] == DRIVER_ROLE) {
            Driver *driver = new Driver(commands[0]);
            users.push_back(driver);
        }
        else if (commands[1] == PASSENGER_ROLE) {
            Passenger *pass = new Passenger(commands[0]);
            users.push_back(pass);
        }
        else {
            throw Error(BAD_REQUEST_ERROR);
        }
    }    
    else {
        throw Error(BAD_REQUEST_ERROR);
    }   
}

void Utaxi::check_duplicated_users(string username) {
    for (int num_of_user = 0; num_of_user < users.size(); num_of_user++) {
        if (users[num_of_user]->get_username() == username) {
            throw Error(BAD_REQUEST_ERROR);
        }
    }
}

int Utaxi::aplly_for_trip(vector <string> &commands) {
    double cost;
    if (commands[0] != "" && commands[1] != "" && commands[2] != "" && commands[3] != "") {                
        int user_index = find_user(commands[0]);
        int origin_index = find_location(commands[1]);
        int destination_index = find_location(commands[2]);
        if (commands[3] != "yes" && commands[3] != "no") {
            throw Error(BAD_REQUEST_ERROR);
        }
        cost = count_price(origin_index, destination_index, commands[3]);
        add_trip_for_passenger(user_index, commands[1], commands[2], commands[3], cost);
        return trips.size();  
    } 
    else {
        throw Error(BAD_REQUEST_ERROR);
    }
}

int Utaxi::find_user(string username) {
    for (int num_of_user = 0; num_of_user < users.size(); num_of_user++) {
        if (users[num_of_user]->get_username() == username) {
            return num_of_user;
        }
        else if (num_of_user == users.size()-1) {
            throw Error(NOT_FOUND_ERROR);
        } 
    }
    throw Error(NOT_FOUND_ERROR);
    return 0;
}

int Utaxi::find_location(string location) {
    for (int num_of_location = 0; num_of_location < address.size(); num_of_location++) {
        if (address[num_of_location]->get_location_name() == location) {
            return num_of_location;
        }
        else if (num_of_location == address.size()-1) {
            throw Error(NOT_FOUND_ERROR);
        } 
    }
    throw Error(NOT_FOUND_ERROR);
    return 0;
}

void Utaxi::add_trip_for_passenger(int user_index, string origin, string destination, string is_in_hurry, double cost) {   
    if (users[user_index]->get_num_of_trips() == 0) {
        users[user_index]->apply_for_trip(trips, origin, destination, trips.size()+1, is_in_hurry, cost);
    }
    else {
        throw Error(BAD_REQUEST_ERROR);
    }
}

vector <Trip*> Utaxi::show_all_trips(vector <string> &commands) {
    if (commands[0] != "" && commands[1] != "") {
        for (int num_of_user = 0; num_of_user < users.size(); num_of_user++) {
            if (users[num_of_user]->get_username() == commands[0]) {
                vector <Trip*> wanted_trips = users[num_of_user]->show_all_trips(trips, commands[1]);
                return wanted_trips;
                break;
            }
        }      
    }
    else {
        throw Error(BAD_REQUEST_ERROR);
    }
}

Trip* Utaxi::show_specefic_trip(vector <string> &commands) {
    int id = stoi(commands[1]);
    if (commands[0] != "" && commands[1] != "") {
        for (int num_of_user = 0; num_of_user < users.size(); num_of_user++) {
            if (users[num_of_user]->get_username() == commands[0]) {
                Trip* wanted_trip = users[num_of_user]->show_specefic_trips(trips, id);
                return wanted_trip;
                break;
            }
        }        
    }
    else {
        throw Error(BAD_REQUEST_ERROR);
    }
}

void Utaxi::delete_trip(vector <string> &commands) {   
    int id = stoi(commands[1]);
    if (commands[0] != "" && commands[1] != "") {      
        match_user_and_id(commands[0], id);
        return;        
    }
    else {
        throw Error(BAD_REQUEST_ERROR);
    }    
}

void Utaxi::match_user_and_id(string username, int id) {
    for (int num_of_user = 0; num_of_user < users.size(); num_of_user++) {
        if (users[num_of_user]->get_username() == username) {
            if (users[num_of_user]->get_trip_id() == id) {
                users[num_of_user]->delete_trip_application(trips, id);
                return;
            }
            else {
                if (id > trips.size()) {
                    throw Error(NOT_FOUND_ERROR);
                }
                else {
                    throw Error(PERMISSION_DENIED_ERROR);
                }
            }
        }
        else if (num_of_user == users.size()) {
            throw Error(NOT_FOUND_ERROR);
        }
    }
    throw Error(NOT_FOUND_ERROR);
}

void Utaxi::accept_trip(vector <string> &commands) {
    int id = stoi(commands[1]);    
    if (commands[0] != "" && commands[1] != "") {
        int user_index = find_user(commands[0]);
        users[user_index]->accept_trip(trips, id-1);
    }
    else {
        throw Error(BAD_REQUEST_ERROR);
    }      
}

void Utaxi::finish_trip(vector <string> &commands) {
    int id = stoi(commands[1]);
    if (commands[0] != "" && commands[1] != "") {                
        int user_index = find_user(commands[0]);
        users[user_index]->finish_trip(trips, id-1);
    }
    else {
        throw Error(BAD_REQUEST_ERROR);
    }
}

double Utaxi::get_price(vector <string> &commands) {
    double price;   
    if (commands[0] != "" && commands[1] != "" && commands[2] != "" && commands[3] != "") {   
        int user_index = find_user(commands[0]);
        int origin_index = find_location(commands[1]);
        int destination_index = find_location(commands[2]);
        if (commands[3] != "yes" && commands[3] != "no") {
            throw Error(BAD_REQUEST_ERROR);
        }
        price = users[user_index]->count_price(address, origin_index, destination_index, commands[3]);
        return price;                  
    }
    else {
        throw Error(BAD_REQUEST_ERROR);
    }
    
}

double Utaxi::count_price(int origin_index, int destination_index, string is_in_hurry) {
    double dist = MAP_SCALE * sqrt(pow(address[origin_index]->get_latitude() - address[destination_index]->get_latitude(), 2) +
                        pow(address[origin_index]->get_longitude() - address[destination_index]->get_longitude(), 2));
    double price = dist * (address[origin_index]->get_trrafic_ratio() + address[destination_index]->get_trrafic_ratio()) * PRICE_CONSTANT;
    if (is_in_hurry == "no") {
        return price;
    }
    else {
        return price * IN_HURRY_COEFFICIENT;
    }
}