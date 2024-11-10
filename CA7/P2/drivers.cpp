#include "drivers.h"

using namespace std;

Driver::Driver(string _username) : User(_username) {}

void Driver::apply_for_trip(vector <Trip*> &trips, string origin, string destination, int id, string is_in_hurry, double cost) {
    throw Error(PERMISSION_DENIED_ERROR);
}

int Driver::get_num_of_trips() {
    return accepted_trip.size();
}

void Driver::show_all_trips(vector <Trip*> trips, string sorted_by_cost) {
    if (trips.size() == 0) {
        throw Error(EMPTY_ERROR);
    }
    else if (sorted_by_cost == "no") {
        show_trips_not_sorted_by_cost(trips);
    }
    else {
        show_trips_sorted_by_cost(trips);
    }
}

void Driver::show_trips_not_sorted_by_cost(vector <Trip*> trips) {
    for (int num_of_trip = 0; num_of_trip < trips.size(); num_of_trip++) {
        trips[num_of_trip]->show_trip();
    }
}

void Driver::show_trips_sorted_by_cost(vector <Trip*> trips) {
    for (int num_of_trip1 = 0; num_of_trip1 < trips.size(); num_of_trip1++) {
        for (int num_of_trip2 = num_of_trip1+1; num_of_trip2 < trips.size(); num_of_trip2++) {
            if (trips[num_of_trip1]->get_cost() < trips[num_of_trip2]->get_cost()) {
                swap(trips[num_of_trip1], trips[num_of_trip2]);
            }
        }
    }
    for (int num_of_trip = 0; num_of_trip < trips.size(); num_of_trip++) {
        trips[num_of_trip]->show_trip();
    }
}

void Driver::show_specefic_trips(vector <Trip*> trips, int id) {
    for (int num_of_trip = 0; num_of_trip < trips.size(); num_of_trip++) {
        if (trips[num_of_trip]->get_id() == id) {
            if (trips[num_of_trip]->get_availability() == YES) {
                trips[num_of_trip]->show_trip();
                break;
            }
            else {
                throw Error(NOT_FOUND_ERROR);
            }    
        }
        else if (num_of_trip == trips.size()-1) {
            throw Error(NOT_FOUND_ERROR);
        }
    } 
}

void Driver::delete_trip_application(vector <Trip*> trips, int id) {
    return;
}

void Driver::accept_trip(vector <Trip*> &trips, int trip_index) {
    if (trips[trip_index]->get_availability() == YES && trips[trip_index]->get_status() == WAITING_STATUS) {
        trips[trip_index]->change_status(TRAVELING_STATUS);
        accepted_trip.push_back(trips[trip_index]);
    }
    else {
        throw Error(BAD_REQUEST_ERROR);
    }
}

void Driver::finish_trip(vector <Trip*> &trips, int trip_index) {
    if (accepted_trip.size() != 0) {
        if (trips[trip_index]->get_availability() == YES && trips[trip_index]->get_status() == TRAVELING_STATUS) {
            trips[trip_index]->change_status(FINISHED_STATUS);
            accepted_trip.clear();
        }
        else {
            throw Error(BAD_REQUEST_ERROR);
        }
    }
    else {
        throw Error(NOT_FOUND_ERROR);
    }
}

double Driver::count_price(vector <Location*> address, int origin_index, int destination_index, string is_in_hurry) {
    throw Error(PERMISSION_DENIED_ERROR);
}