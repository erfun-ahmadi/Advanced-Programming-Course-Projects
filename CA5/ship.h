#ifndef SHIP_H
#define SHIP_H
#include "rsdl.hpp"
#include "const_values.h"

class Ship {
private:
    int coordinate_of_row, coordinate_of_col;
    int is_available = YES;
    int direction;
    int have_shield = NO;
    int increased_shot_speed = NO;
public:
    Ship(int _row, int _col, int _direction);
    void player_direction(char pressed_char);
    void move_player(int col, int row);
    void stop_player();
    void move_enemy(int col);
    void draw_ships(Window *window, std::string photo_name);
    int get_coordinate_of_row();
    int get_coordinate_of_col();
    int get_availability();
    void set_availability(int situation);
    void set_shield();
    void set_increased_shot_speed();
    void remove_shield();
    void remove_increased_shot_speed();
    int have_shield_or_not();
    int increased_shot_speed_or_not();
};

#endif