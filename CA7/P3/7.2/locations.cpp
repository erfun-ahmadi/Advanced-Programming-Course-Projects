#include "locations.h"

using namespace std;

Location::Location(string _name, double _latitude, double _lonitude, int _traffic) {
    location_name = _name;
    latitude = _latitude;
    longitude = _lonitude;
    traffic_ratio = _traffic;
}

string Location::get_location_name() {
    return location_name;
}

double Location::get_latitude() {
    return latitude;
}

double Location::get_longitude() {
    return longitude;
}

int Location::get_trrafic_ratio() {
    return traffic_ratio;
}