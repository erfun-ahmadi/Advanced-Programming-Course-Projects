#include "passengers.h"

using namespace std;

Passenger::Passenger(string _username) : User(_username) {}

void Passenger::apply_for_trip(vector <Trip*> &trips, string origin, string destination, int id) {
    trip_id = id;
    Trip *trip = new Trip(username, origin, destination, id);
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

void Passenger::show_all_trips(vector <Trip*> trips) {
    throw Error(PERMISSION_DENIED_ERROR);
}

void Passenger::show_specefic_trips(vector <Trip*> trips, int id) {
    throw Error(PERMISSION_DENIED_ERROR);
}

void Passenger::delete_trip_application(vector <Trip*> trips, int id) {
    if (passenger_trip[0]->get_status() == WAITING_STATUS) {
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

