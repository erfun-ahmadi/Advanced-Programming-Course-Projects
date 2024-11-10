#include "passengers.h"

using namespace std;

Passenger::Passenger(string _username) : User(_username) {}

void Passenger::apply_for_trip(vector <Trip*> &trips, string origin, string destination, int id, string is_in_hurry, double cost) {
    trip_id = id;
    Trip *trip = new Trip(username, origin, destination, id, is_in_hurry, cost);
    passenger_trip.push_back(trip);
    trips.push_back(trip);
}

int Passenger::get_num_of_trips() {
    if (passenger_trip.size() != 0 && passenger_trip[passenger_trip.size()-1]->get_status() == FINISHED_STATUS) {
        return 0;
    }
    else {
        return passenger_trip.size();
    }
}

vector <Trip*> Passenger::show_all_trips(vector <Trip*> trips, string sorted_by_cost) {
    throw Error(PERMISSION_DENIED_ERROR);
}

Trip* Passenger::show_specefic_trips(vector <Trip*> trips, int id) {
    throw Error(PERMISSION_DENIED_ERROR);
}

void Passenger::delete_trip_application(vector <Trip*> trips, int id) {
    if (passenger_trip[passenger_trip.size()-1]->get_status() == WAITING_STATUS) {
        for (int num_of_trip = 0; num_of_trip < trips.size(); num_of_trip++) {
            if (trips[num_of_trip]->get_id() == id) {
                delete trips[num_of_trip];
                trips[num_of_trip]->change_availability();
            }
        }
        passenger_trip.clear();
    }
    else {
        throw Error(BAD_REQUEST_ERROR);
    }
}

void Passenger::accept_trip(vector <Trip*> &trips, int trip_index) {
    throw Error(PERMISSION_DENIED_ERROR);
}

void Passenger::finish_trip(vector <Trip*> &trips, int trip_index) {
    throw Error(PERMISSION_DENIED_ERROR);
}

double Passenger::count_price(vector <Location*> address, int origin_index, int destination_index, string is_in_hurry) {
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

