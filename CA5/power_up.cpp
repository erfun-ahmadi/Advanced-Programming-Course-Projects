#include "power_up.h"
#include <string>

using namespace std;

PowerUp::PowerUp(int _row, int _col, int _type) {
    coordinate_of_row = _row;
    coordinate_of_col = _col;
    type_of_power = _type;
}

void PowerUp::draw_power(Window *window, string filename) {
    time_to_hide_power += 1;
    if (time_to_hide_power <= TIME_TO_HIDE_POWER && is_available == YES) {
        window->draw_img(filename, Rectangle(Point(coordinate_of_col, coordinate_of_row), Point(coordinate_of_col+SHIP_COL_SCALE,
        coordinate_of_row+SHIP_ROW_SCALE)));
    }
    else {
        is_available = NO;
    }
}

int PowerUp::get_coordinate_of_row() {
    return coordinate_of_row;
}

int PowerUp::get_coordinate_of_col() {
    return coordinate_of_col;
}

int PowerUp::get_availability() {
    return is_available;
}

int PowerUp::get_type_of_power() {
    return type_of_power;
}

void PowerUp::remove_availability() {
    is_available = NO;
}