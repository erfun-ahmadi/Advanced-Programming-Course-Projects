#include "shot.h"

Shot::Shot(Window *window, int _row, int _col, int _side) {
    coordinate_of_row = _row;
    coordinate_of_col = _col;
    side = _side;
    window->play_sound_effect("Rifle_Firing_Sound_Effect.mp3");
}

void Shot::draw_shot(Window *window) {
    if (is_available == YES) {
        if (side == PLAYER_SHOT) {
            window->draw_img("player shot.png", Rectangle(Point(coordinate_of_col, coordinate_of_row), 
            Point(coordinate_of_col+SHOT_COL_SCALE, coordinate_of_row+SHOT_ROW_SCALE)));
        }
        else if (side == ENEMY_SHOT) {
            window->draw_img("enemy shot.png", Rectangle(Point(coordinate_of_col, coordinate_of_row), 
            Point(coordinate_of_col+SHOT_COL_SCALE, coordinate_of_row+SHOT_ROW_SCALE)));
        }
    } 
}

void Shot::move_regular_shot() {
    if (side == PLAYER_SHOT) {       
        coordinate_of_row -= NORMAL_SHOT_SPEED;        
    }
    else if (side == ENEMY_SHOT) {
        coordinate_of_row += NORMAL_SHOT_SPEED;
    }
}

void Shot::move_powered_shot() {
    coordinate_of_row -= INCREASED_SHOT_SPEED;
}

int Shot::get_coordinate_of_row() {
    return coordinate_of_row;
}

int Shot::get_coordinate_of_col() {
    return coordinate_of_col;
}

int Shot::get_shot_situation() {
    return is_shot;
}

int Shot::get_availability() {
    return is_available;
}

void Shot::set_availability(int situation) {
    is_available = situation;
}