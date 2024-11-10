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

void Utaxi::post_command(vector <string> &commands) {
    if (commands[0] == SIGNUP) {
        commands.erase(commands.begin(), commands.begin()+1);
        signup(commands);
    }
    else if (commands[0] == TRIPS) {
        commands.erase(commands.begin(), commands.begin()+1);
        aplly_for_trip(commands);
    }
    else if (commands[0] == ACCEPT) {
        commands.erase(commands.begin(), commands.begin()+1);
        accept_trip(commands);
    }
    else if (commands[0] == FINISH) {
        commands.erase(commands.begin(), commands.begin()+1);
        finish_trip(commands);
    }
    else {
        cout << NOT_FOUND_ERROR << endl;
    }
}

void Utaxi::get_command(vector <string> &commands) {
    if (commands[0] == TRIPS) {
        commands.erase(commands.begin(), commands.begin()+1);
        show_trips(commands);
    }
    else if (commands[0] == COST) {
        commands.erase(commands.begin(), commands.begin()+1);
        get_price(commands);
    }
    else {
        cout << NOT_FOUND_ERROR << endl;
    }
}

void Utaxi::delete_command(vector <string> &commands) {
    if (commands[0] == TRIPS) {
        commands.erase(commands.begin(), commands.begin()+1);
        delete_trip(commands);
    }
    else {
        cout << NOT_FOUND_ERROR << endl;
    }
}

int Utaxi::find_specific_command(vector <string> commands, string each_command, string &argument) {
    if (find(commands.begin(), commands.end(), each_command) != commands.end()) {
        argument = commands[find_needed_command(commands, each_command)];
        return YES;
    }
    return NO;
}

int Utaxi::find_username_command(vector <string> commands, string &username) {
    return find_specific_command(commands, USERNAME, username);
}

int Utaxi::find_role_command(vector <string> commands, string &role) {
    return find_specific_command(commands, ROLE, role);
}

int Utaxi::find_origin_command(vector <string> commands, string &origin) {
    return find_specific_command(commands, ORIGIN, origin);
}

int Utaxi::find_destination_command(vector <string> commands, string &destination) {
    return find_specific_command(commands, DESTINATION, destination);
}

int Utaxi::find_id_command(vector <string> commands, int &id) {
    if (find(commands.begin(), commands.end(), ID) != commands.end()) {
        id = stoi(commands[find_needed_command(commands, ID)]);
        return YES;
    }
    return NO;
}

int Utaxi::find_in_hurry_command(vector <string> commands, string &is_in_hurry) {
    return find_specific_command(commands, IN_HURRY, is_in_hurry);
}

int Utaxi::find_sort_by_cost_command(vector <string> commands, string &sorted_by_cost) {
    return find_specific_command(commands, SORT_BY_COST, sorted_by_cost);
}

void Utaxi::signup(vector <string> &commands) {
    string username, role;
    if (commands[0] == SEPERATOR) {
        commands.erase(commands.begin(), commands.begin()+1);
        if (commands.size() == 4) {
            if (find_role_command(commands, role) == YES && find_username_command(commands, username) == YES) {
                try {
                    check_duplicated_users(username);
                    if (role == DRIVER_ROLE) {
                        Driver *driver = new Driver(username);
                        users.push_back(driver);
                        cout << OK << endl;
                    }
                    else if (role == PASSENGER_ROLE) {
                        Passenger *pass = new Passenger(username);
                        users.push_back(pass);
                        cout << OK << endl;
                    }
                    else {
                        cout << BAD_REQUEST_ERROR << endl;
                    }
                }
                catch (Error &er){
                    er.show_error();
                }
            }
            else {
                cout << BAD_REQUEST_ERROR << endl;
            }
        }    
        else {
            cout << BAD_REQUEST_ERROR << endl;
        }
    }    
    else {
        cout << BAD_REQUEST_ERROR << endl;
    }
}

void Utaxi::check_duplicated_users(string username) {
    for (int num_of_user = 0; num_of_user < users.size(); num_of_user++) {
        if (users[num_of_user]->get_username() == username) {
            throw Error(BAD_REQUEST_ERROR);
        }
    }
}

void Utaxi::aplly_for_trip(vector <string> &commands) {
    string username, origin, destination, is_in_hurry;
    double cost;
    if (commands[0] == SEPERATOR) {
       commands.erase(commands.begin(), commands.begin()+1);
        if (commands.size() == 8) {
            if (find_origin_command(commands, origin) == YES && find_destination_command(commands, destination) == YES &&
                find_username_command(commands, username) == YES && find_in_hurry_command(commands, is_in_hurry) == YES) {
                try {
                    int user_index = find_user(username);
                    int origin_index = find_location(origin);
                    int destination_index = find_location(destination);
                    cost = count_price(origin_index, destination_index, is_in_hurry);
                    add_trip_for_passenger(user_index, origin, destination, is_in_hurry, cost);
                    cout << trips.size() << endl;
                }
                catch (Error &er) {
                    er.show_error();
                }
            }
            else {
                cout << BAD_REQUEST_ERROR << endl;
            }
        } 
        else {
            cout << BAD_REQUEST_ERROR << endl;
        }
    }
    else {
        cout << BAD_REQUEST_ERROR << endl;
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

int Utaxi::find_trip(int id) {
    for (int num_of_trip = 0; num_of_trip < trips.size(); num_of_trip++) {
        if (trips[num_of_trip]->get_id() == id) {
            return num_of_trip;
        }
        else if (num_of_trip == trips.size()-1) {
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

void Utaxi::show_trips(vector <std::string> &commands) {
    string sorted_by_cost;
    int id;
    if (commands[0] == SEPERATOR) {
        commands.erase(commands.begin(), commands.begin()+1);
        if (commands.size() == 4) {
            if (find_sort_by_cost_command(commands, sorted_by_cost) == YES) {
                show_all_trips(commands, sorted_by_cost);
            }
            else if (find_id_command(commands, id) == YES) {
                show_specefic_trip(commands, id);
            }
            else {
                cout << BAD_REQUEST_ERROR <<  endl;
            }
        }
        else {
            cout << BAD_REQUEST_ERROR <<  endl;
        }
    }
    else {
        cout << BAD_REQUEST_ERROR << endl;
    }
}

void Utaxi::show_all_trips(vector <string> &commands, string sorted_by_cost) {
    string username;
    if (find_username_command(commands, username) == YES) {
        try {
            for (int num_of_user = 0; num_of_user < users.size(); num_of_user++) {
                if (users[num_of_user]->get_username() == username) {
                    users[num_of_user]->show_all_trips(trips, sorted_by_cost);
                    break;
                }
            }
        }
        catch (Error &er) {
            er.show_error();   
        }
    }
    else {
        cout << BAD_REQUEST_ERROR << endl;
    }
}

void Utaxi::show_specefic_trip(vector <string> &commands, int id) {
    string username;
    if (find_username_command(commands, username) == YES) {
        try {
            for (int num_of_user = 0; num_of_user < users.size(); num_of_user++) {
                if (users[num_of_user]->get_username() == username) {
                    users[num_of_user]->show_specefic_trips(trips, id);
                    break;
                }
            }
        }
        catch (Error &er) {
            er.show_error();   
        }
    }
    else {
        cout << BAD_REQUEST_ERROR << endl;
    }
}

void Utaxi::delete_trip(vector <string> &commands) {
    string username;
    int id;
    if (commands[0] == SEPERATOR) {
       commands.erase(commands.begin(), commands.begin()+1);
        if (commands.size() == 4) {
            if (find_username_command(commands, username) == YES && find_id_command(commands, id) == YES) {
                try {
                    match_user_and_id(username, id);
                    cout << OK << endl;
                }
                catch (Error &er) {
                    er.show_error();
                }
            }
            else {
                cout << BAD_REQUEST_ERROR << endl;
            }
        }
        else {
            cout << BAD_REQUEST_ERROR << endl;
        }
    }
    else {
        cout << BAD_REQUEST_ERROR << endl;
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
}

void Utaxi::accept_trip(vector <string> &commands) {
    string username;
    int id;
    if (commands[0] == SEPERATOR) {
       commands.erase(commands.begin(), commands.begin()+1);
        if (commands.size() == 4) {
            if (find_username_command(commands, username) == YES && find_id_command(commands, id) == YES) {
                try {
                    int user_index = find_user(username);
                    int trip_index = find_trip(id);
                    add_trip_for_driver(user_index, trip_index);
                    cout << OK << endl;
                }
                catch (Error &er) {
                    er.show_error();
                }
            }
            else {
                cout << BAD_REQUEST_ERROR << endl;
            }
        }
        else {
            cout << BAD_REQUEST_ERROR << endl;
        }
    }   
    else {
        cout << BAD_REQUEST_ERROR << endl;
    }
}

void Utaxi::add_trip_for_driver(int user_index, int trip_index) {
    if (users[user_index]->get_num_of_trips() == 0) {
        users[user_index]->accept_trip(trips, trip_index);
    }
    else {
        throw Error(BAD_REQUEST_ERROR);
    }
}

void Utaxi::finish_trip(vector <string> &commands) {
    string username;
    int id;
    if (commands[0] == SEPERATOR) {
       commands.erase(commands.begin(), commands.begin()+1);
        if (commands.size() == 4) {
            if (find_username_command(commands, username) == YES && find_id_command(commands, id) == YES) {
                try {
                    int user_index = find_user(username);
                    int trip_index = find_trip(id);
                    remove_trip_for_driver_and_passenger(user_index, trip_index);
                    cout << OK << endl;
                }
                catch (Error &er) {
                    er.show_error();
                }
            }
            else {
                cout << BAD_REQUEST_ERROR << endl;
            }
        }
        else {
            cout << BAD_REQUEST_ERROR << endl;
        }
    }
    else {
        cout << BAD_REQUEST_ERROR << endl;
    }
}

void Utaxi::remove_trip_for_driver_and_passenger(int user_index, int trip_index) {   
    users[user_index]->finish_trip(trips, trip_index);   
}

void Utaxi::get_price(vector <string> &commands) {
    string username, origin, destination, is_in_hurry;
    double price;
    if (commands[0] == SEPERATOR) {
       commands.erase(commands.begin(), commands.begin()+1);
        if (commands.size() == 8) {
            if (find_username_command(commands, username) == YES && find_origin_command(commands, origin) == YES &&
                find_destination_command(commands, destination) == YES && find_in_hurry_command(commands, is_in_hurry) == YES) {
                try {
                    int user_index = find_user(username);
                    int origin_index = find_location(origin);
                    int destination_index = find_location(destination);
                    price = users[user_index]->count_price(address, origin_index, destination_index, is_in_hurry);
                    cout << price << endl;
                }
                catch (Error &er) {
                    er.show_error();
                }
            }
            else {
                cout << BAD_REQUEST_ERROR << endl;
            }
        }
        else {
            cout << BAD_REQUEST_ERROR << endl;
        }
    }
    else {
        cout << BAD_REQUEST_ERROR << endl;
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

int Utaxi::find_needed_command(vector <string> commands, string needed_command) {
    for (int num_of_index = 0; num_of_index < commands.size(); num_of_index++) {
        if (commands[num_of_index] == needed_command) {
            return num_of_index+1;
        }
    }
    return 0;
}