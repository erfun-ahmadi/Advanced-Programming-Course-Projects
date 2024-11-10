#include "utaxi.h"
#include <iostream>
#include <fstream>

using namespace std;

void Utaxi::add_locations(char* argv[]) {
    string each_location;
    ifstream location_file(argv[1]);
    getline(location_file, each_location);
    while (getline(location_file, each_location)) {
        string name;
        float latitude, longitude;
        size_t index = each_location.find(',');
        name = each_location.substr(0, index);
        each_location = each_location.substr(index + 1);
        index = each_location.find(',');
        latitude = stod(each_location.substr(0, index));
        each_location = each_location.substr(index + 1);
        longitude = stod(each_location);
        address.push_back(Location(name, latitude, longitude));
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
}

void Utaxi::get_command(vector <string> &commands) {
    if (commands[0] == TRIPS) {
        commands.erase(commands.begin(), commands.begin()+1);
        show_trips(commands);
    }
}

void Utaxi::delete_command(vector <string> &commands) {
    if (commands[0] == TRIPS) {
        commands.erase(commands.begin(), commands.begin()+1);
        delete_trip(commands);
    }
}

void Utaxi::signup(vector <string> &commands) {
    string username, role;
    if (commands[0] == SEPERATOR) {
        commands.erase(commands.begin(), commands.begin()+1);
        if (commands.size() == 4) {
            if (set_user_and_role(commands, username, role) == 1) {
                try {
                    check_duplicated_users(username);
                    if (role == DRIVER_ROLE) {
                        Driver *driver = new Driver(username);
                        users.push_back(driver);
                    }
                    else if (role == PASSENGER_ROLE) {
                        Passenger *pass = new Passenger(username);
                        users.push_back(pass);
                    }
                    cout << OK << endl;
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

int Utaxi::set_user_and_role(vector <string> &commands, string &username, string &role) {
    if (find(commands.begin(), commands.end(), USERNAME) != commands.end() && 
        find(commands.begin(), commands.end(), ROLE) != commands.end()) {
        username = commands[find_needed_command(commands, USERNAME)];
        role = commands[find_needed_command(commands, ROLE)];
        return 1;
    }
    return 0;
}

void Utaxi::check_duplicated_users(string username) {
    for (int num_of_user = 0; num_of_user < users.size(); num_of_user++) {
        if (users[num_of_user]->get_username() == username) {
            throw Error(BAD_REQUEST_ERROR);
        }
    }
}

void Utaxi::aplly_for_trip(vector <string> &commands) {
    string username, origin, destination;
    if (commands[0] == SEPERATOR) {
       commands.erase(commands.begin(), commands.begin()+1);
        if (commands.size() == 6) {
            if (set_user_and_location(commands, username, origin, destination) == 1) {
                try {
                    int user_index = find_user(username);
                    int origin_index = find_location(origin);
                    int destination_index = find_location(destination);
                    add_trip_for_passenger(user_index, origin, destination);
                    cout << trips.size() << endl;
                }
                catch (Error &er) {
                    er.show_error();
                }
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

int Utaxi::set_user_and_location(vector <string> &commands, string &username, string &origin, string &destination) {
    if (find(commands.begin(), commands.end(), USERNAME) != commands.end() && 
        find(commands.begin(), commands.end(), ORIGIN) != commands.end() &&
        find(commands.begin(), commands.end(), DESTINATION) != commands.end()) {
        username = commands[find_needed_command(commands, USERNAME)];
        origin = commands[find_needed_command(commands, ORIGIN)];
        destination = commands[find_needed_command(commands, DESTINATION)];
        return 1;
    }
    return 0;
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
        if (address[num_of_location].get_location_name() == location) {
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

void Utaxi::add_trip_for_passenger(int user_index, string origin, string destination) {   
    if (users[user_index]->get_num_of_trips() == 0) {
        users[user_index]->apply_for_trip(trips, origin, destination, trips.size()+1);
    }
    else {
        throw Error(BAD_REQUEST_ERROR);
    }
}

void Utaxi::show_trips(vector <std::string> &commands) {
    string username;
    int id;
    if (commands[0] == SEPERATOR) {
        commands.erase(commands.begin(), commands.begin()+1);
        if (commands.size() == 2) {
            show_all_trips(commands);
        }
        else if (commands.size() == 4) {
            show_specefic_trip(commands);
        }
        else {
            cout << BAD_REQUEST_ERROR <<  endl;
        }
    }
    else {
        cout << BAD_REQUEST_ERROR << endl;
    }
}

void Utaxi::show_all_trips(vector <string> &commands) {
    string username = commands[1];
    try {
        for (int num_of_user = 0; num_of_user < users.size(); num_of_user++) {
            if (users[num_of_user]->get_username() == username) {
                users[num_of_user]->show_all_trips(trips);
                break;
            }
        }
    }
    catch (Error &er) {
        er.show_error();   
    }
}

void Utaxi::show_specefic_trip(vector <string> &commands) {
    string username;
    int id;
    if (set_user_and_id(commands, username, id) == 1) {
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

int Utaxi::set_user_and_id(vector <string> &commands, string &username, int &id) {
    if (find(commands.begin(), commands.end(), USERNAME) != commands.end() && 
        find(commands.begin(), commands.end(), ID) != commands.end()) {
        username = commands[find_needed_command(commands, USERNAME)];
        id = stoi(commands[find_needed_command(commands, ID)]);
        return 1;
    }
    return 0;
}

void Utaxi::delete_trip(vector <string> &commands) {
    string username;
    int id;
    if (commands[0] == SEPERATOR) {
       commands.erase(commands.begin(), commands.begin()+1);
        if (commands.size() == 4) {
            if (set_user_and_id(commands, username, id) == 1) {
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
            if (set_user_and_id(commands, username, id) == 1) {
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
            if (set_user_and_id(commands, username, id) == 1) {
                try {
                    int user_index = find_user(username);
                    int trip_index = find_trip(id);
                    remove_trip_for_driver(user_index, trip_index);
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

void Utaxi::remove_trip_for_driver(int user_index, int trip_index) {   
    users[user_index]->finish_trip(trips, trip_index);   
}

int Utaxi::find_needed_command(vector <string> commands, string needed_command) {
    for (int num_of_index = 0; num_of_index < commands.size(); num_of_index++) {
        if (commands[num_of_index] == needed_command) {
            return num_of_index+1;
        }
    }
    return 0;
}