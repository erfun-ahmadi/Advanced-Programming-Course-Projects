#ifndef GAME_H
#define GAME_H
#include <vector>
#include "const_values.h"
#include "ship.h"
#include "shot.h"
#include "power_up.h"


class Game {
private:
    int num_of_level = 1;
    int num_of_levels;
    int pressed_space_before = NO;
    int player_lost = NO;
    int level_is_started = NO;
    int immobile_time_to_shoot = PERIOD_BETWEEN_IMMOBILE_SHOTS/2;
    int moving_time_to_shoot = PERIOD_BETWEEN_MOVING_SHOTS/2;
    int num_of_unavailable_enemies = 0;
    int time_to_hide_power = 0;
    int time_to_lose_shield = 0;
    int time_to_lose_shot_speed = 0;
public:
    int row, col;
    std::vector <Ship> immobile_enemy;
    std::vector <Ship> hostage;
    std::vector <Ship> moving_enemy;
    std::vector <Ship> player;
    std::vector <Shot> player_shot;
    std::vector <Shot> immobile_enemy_shot;
    std::vector <Shot> moving_enemy_shot; 
    std::vector <PowerUp> shield;
    std::vector <PowerUp> increase_shot_speed;
    Game(std::vector <std::string> &game_map); 
    void specify_game_info(std::vector <std::string> &game_map);
    void get_events(Window *window);  
    void locate_ships(std::vector <std::string> &game_map);
    void move_ships();
    void draw_ships(Window *window); 
    void shoot_to_enemy(Window *window, std::vector <Ship> &enemy);
    void create_power_up(int row_of_destroyed_enemy, int col_of_destroyed_enemy);
    void draw_power_up(Window *window, std::vector <PowerUp> &power_up, std::string filename);
    void get_power_up(std::vector <PowerUp> &power_up);
    void lose_power_up();
    void shoot_to_hostage();
    void player_shooting(Window *window);
    void enemy_shooting(Window *window, std::vector <Ship> enemy, std::vector <Shot> &enemy_shot, int period_between_shots, int &time_to_shoot);
    void get_shot(std::vector <Shot> &enemy_shot);
    void ships_collide(std::vector <Ship> enemy);
    void win_the_level();
    void lose_the_game(Window *window);
    void win_the_game(Window *window);
};

#endif