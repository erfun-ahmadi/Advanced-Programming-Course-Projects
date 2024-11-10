#include "ship.h"

using namespace std;

Ship::Ship(int _row, int _col, int _direction) {
    coordinate_of_row = _row;
    coordinate_of_col = _col;
    direction = _direction;
}

void Ship::player_direction(char pressed_char) {
    if (pressed_char == LEFT_BUTTON) {
        direction = LEFT_DIRECTION;
    }
    if (pressed_char == UP_BUTTON) {
        direction = UP_DIRECTION;
    }
    if (pressed_char == DOWN_BUTTON) {
        direction = DOWN_DIRECTION;
    }
    if (pressed_char == RIGHT_BUTTON) {
        direction = RIGHT_DIRECTION;
    }
}

void Ship::move_player(int col, int row) {
    if (direction == LEFT_DIRECTION) {       
        if (coordinate_of_col > 0) {
            coordinate_of_col -= SHIP_SPEED;
        }
    }
    if (direction == UP_DIRECTION) {       
        if (coordinate_of_row > 0) {
            coordinate_of_row -= SHIP_SPEED;
        }
    }
    if (direction == DOWN_DIRECTION) {       
        if (coordinate_of_row + SHIP_ROW_SCALE < row) {
            coordinate_of_row += SHIP_SPEED;
        }
    }
    if (direction == RIGHT_DIRECTION) {       
        if (coordinate_of_col + SHIP_COL_SCALE < col) {
            coordinate_of_col += SHIP_SPEED;
        }
    }
}

void Ship::stop_player() {
    direction = STABLE;
}

void Ship::move_enemy(int col) {
    if (is_available == YES) {
        if (direction == RIGHT_DIRECTION) {
            coordinate_of_col += SHIP_SPEED;
            if (coordinate_of_col + SHIP_COL_SCALE >= col) {
                direction = LEFT_DIRECTION;
            }
        }
        else if (direction == LEFT_DIRECTION) {
            coordinate_of_col -= SHIP_SPEED;
            if (coordinate_of_col <= 0) {
                direction = RIGHT_DIRECTION;
            }
        }
    }     
}

void Ship::draw_ships(Window *window, string photo_name) {
    if (is_available == YES) {
        window->draw_img(photo_name, Rectangle(Point(coordinate_of_col,coordinate_of_row), Point(coordinate_of_col + SHIP_COL_SCALE, 
        coordinate_of_row + SHIP_ROW_SCALE)));
    }        
}

int Ship::get_coordinate_of_col() {
    return coordinate_of_col;
}

int Ship::get_coordinate_of_row() {
    return coordinate_of_row;
}

int Ship::get_availability() {
    return is_available;
}

void Ship::set_availability(int situation) {
    is_available = situation;
}

void Ship::set_shield() {
    have_shield = YES;
}

void Ship::set_increased_shot_speed() {
    increased_shot_speed = YES;
}

void Ship::remove_shield() {
    have_shield = NO;
}

void Ship::remove_increased_shot_speed() {
    increased_shot_speed = NO;
}

int Ship::have_shield_or_not() {
    return have_shield;
}

int Ship::increased_shot_speed_or_not() {
    return increased_shot_speed;
}