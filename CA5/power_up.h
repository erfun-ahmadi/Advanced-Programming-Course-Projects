#ifndef POWER_H
#define POWER_H
#include "const_values.h"
#include "rsdl.hpp"

class PowerUp {
private:
    int coordinate_of_row, coordinate_of_col;
    int type_of_power;
    int is_available = YES;
    int time_to_hide_power = 0;
public:
    PowerUp(int _row, int _col, int _type);
    void draw_power(Window *window, std::string filename);
    int get_coordinate_of_row();
    int get_coordinate_of_col();
    int get_availability();
    int get_type_of_power();
    void remove_availability();
};

#endif 