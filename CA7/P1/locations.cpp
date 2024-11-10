#include "locations.h"

using namespace std;

Location::Location(string _name, double _latitude, double _lonitude) {
    location_name = _name;
    latitude = _latitude;
    longitude = _lonitude;
}

string Location::get_location_name() {
    return location_name;
}