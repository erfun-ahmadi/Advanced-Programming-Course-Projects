#ifndef SHOT_H
#define SHOT_H
#include "const_values.h"
#include "rsdl.hpp"

class Shot {
private:
    int coordinate_of_row, coordinate_of_col;
    int is_shot = YES;
    int is_available = YES;
    int side;
public:    
    Shot(Window *window, int _row, int _col, int _side);
    void draw_shot(Window *window);
    void move_regular_shot();
    void move_powered_shot();
    int get_coordinate_of_row();
    int get_coordinate_of_col();  
    int get_shot_situation();  
    int get_availability();
    void set_availability(int situation);
};

#endif