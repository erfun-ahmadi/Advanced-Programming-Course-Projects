#ifndef LOCATIONS_H
#define LOCATIONS_H

#include <string>

class Location {
private:
    std::string location_name;
    double latitude;
    double longitude;
    int traffic_ratio;
public:    
    Location(std::string _name, double _latitude, double _lonitude, int _trrafic);
    std::string get_location_name();
    double get_latitude();
    double get_longitude();
    int get_trrafic_ratio();
};

#endif