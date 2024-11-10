#include "trips.h"
#include <iostream>

using namespace std;

Trip::Trip(string _username, string _origin, string _destination, int _id, string _is_in_hurry, double _cost) {
    username = _username;
    origin = _origin;
    destination = _destination;
    trip_id = _id;
    is_in_hurry = _is_in_hurry;
    cost = _cost;
}

void Trip::show_trip() {
    if (is_available == YES) {
        cout << trip_id << " " << username << " " << origin << " " << destination << " " << cost << " " << status << endl;
    }
}

int Trip::get_id() {
    return trip_id;
}

string Trip::get_status() {
    return status;
}

void Trip::change_availability() {
    is_available = NO;
}

int Trip::get_availability() {
    return is_available;
}

void Trip::change_status(string new_status) {
    status = new_status;
}

double Trip::get_cost() {
    return cost;
}
