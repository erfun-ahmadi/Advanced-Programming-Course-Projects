#ifndef LOCATIONS_H
#define LOCATION_H

#include <string>

class Location {
private:
    std::string location_name;
    double latitude;
    double longitude;
public:    
    Location(std::string _name, double _latitude, double _lonitude);
    std::string get_location_name();
};

#endif