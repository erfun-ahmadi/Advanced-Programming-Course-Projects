#include "game.h"
#include <stdlib.h>

using namespace std;

Game::Game(vector <string> &game_map) {
    specify_game_info(game_map);
    Window *window = new Window(col*MAP_SCALE, row*MAP_SCALE, "StarWars");    
    window->play_music("FanfareAndPrologue.mp3");
    while(true) {
        if (player_lost == NO) {
            if (num_of_level <= num_of_levels) {
                if (level_is_started == NO) {
                    locate_ships(game_map);
                } 
                else if (level_is_started == YES) {
                    window->draw_img("background.jpg", Rectangle(0, 0, col*MAP_SCALE, row*MAP_SCALE));                       
                    get_events(window);       
                    draw_ships(window); 
                    move_ships();
                    player_shooting(window); 
                    enemy_shooting(window, immobile_enemy, immobile_enemy_shot, PERIOD_BETWEEN_IMMOBILE_SHOTS, immobile_time_to_shoot);
                    enemy_shooting(window, moving_enemy, moving_enemy_shot, PERIOD_BETWEEN_MOVING_SHOTS, moving_time_to_shoot);   
                    shoot_to_enemy(window, moving_enemy);
                    shoot_to_enemy(window, immobile_enemy);
                    draw_power_up(window, shield, "shield.png");
                    draw_power_up(window, increase_shot_speed, "trooper.png");
                    get_power_up(increase_shot_speed);
                    get_power_up(shield);
                    lose_power_up();
                    shoot_to_hostage();
                    get_shot(immobile_enemy_shot);
                    get_shot(moving_enemy_shot);
                    ships_collide(immobile_enemy);
                    ships_collide(moving_enemy);
                    ships_collide(hostage);
                    win_the_level();
                    delay(15);
                }
            }
            else {
                win_the_game(window);
                get_events(window);
            }
        }
        else if (player_lost == YES) {
            lose_the_game(window);
            get_events(window);  
        }
        window->update_screen();  
    } 
}

void Game::specify_game_info(vector <string> &game_map) {
    string space_delimiter = " ";
    int pos = game_map[0].find(space_delimiter);
    row = stoi(game_map[0].substr(0, pos));
    game_map[0].erase(0, pos+space_delimiter.length());
    pos = game_map[0].find(space_delimiter);
    col = stoi(game_map[0].substr(0, pos));
    num_of_levels = stoi(game_map[1]);
    game_map.erase(game_map.begin(), game_map.begin()+2);
}

void Game::get_events(Window *window) {
    Event event = window->poll_for_event();
    if (event.get_type() == Event::QUIT) { 
        exit(0);
    }
    if (event.get_type() == Event::KEY_PRESS) {
        char pressed_char = event.get_pressed_key();
        if (pressed_char != ' ') {
            player[0].player_direction(pressed_char);
        }
        else {
            player_shot.push_back(Shot(window, player[0].get_coordinate_of_row(), 
            player[0].get_coordinate_of_col()+(SHIP_COL_SCALE/2), PLAYER_SHOT));
            pressed_space_before = YES;
        }    
    }    
    if (event.get_type() == Event::KEY_RELEASE) {
        player[0].stop_player();
    }
}

void Game::locate_ships(vector <string> &game_map) {
    int num_of_line = 0;
    while (num_of_line < row) {
        for (int num_of_col = 0; num_of_col < col; num_of_col++) {
            if (game_map[num_of_line][num_of_col] == 'E') {
                immobile_enemy.push_back(Ship(num_of_line*MAP_SCALE, num_of_col*MAP_SCALE, STABLE));
            }
            else if (game_map[num_of_line][num_of_col] == 'S') {
                hostage.push_back(Ship(num_of_line*MAP_SCALE, num_of_col*MAP_SCALE, STABLE));
            }
            else if (game_map[num_of_line][num_of_col] == 'M') {
                moving_enemy.push_back(Ship(num_of_line*MAP_SCALE, num_of_col*MAP_SCALE, RIGHT_DIRECTION));
            }
        }
        num_of_line += 1;
    }
    if (num_of_level < num_of_levels) {
        game_map.erase(game_map.begin(), game_map.begin()+num_of_line+1);
    }
    else {
        game_map.erase(game_map.begin(), game_map.begin()+num_of_line);
    }
    int player_col = rand() % col;
    player.push_back(Ship((row-1)*MAP_SCALE, player_col*MAP_SCALE, STABLE));
    level_is_started = YES;
    num_of_unavailable_enemies = 0;
}

void Game::move_ships() {
    player[0].move_player(col*MAP_SCALE, row*MAP_SCALE);     
    for (int num_of_enemy = 0; num_of_enemy < moving_enemy.size(); num_of_enemy++) {
        moving_enemy[num_of_enemy].move_enemy(col*MAP_SCALE);
    }
}

void Game::draw_ships(Window *window) {
    for (int num_of_immobile = 0; num_of_immobile < immobile_enemy.size(); num_of_immobile++) {
        immobile_enemy[num_of_immobile].draw_ships(window, "immobile enemy.png");
    }
    for (int num_of_hostage = 0; num_of_hostage < hostage.size(); num_of_hostage++) {
        hostage[num_of_hostage].draw_ships(window, "hostage.png");
    }
    for (int num_of_moving = 0; num_of_moving < moving_enemy.size(); num_of_moving++) {
        moving_enemy[num_of_moving].draw_ships(window, "moving enemy.png");
    }
    for (int num_of_player = 0; num_of_player < player.size(); num_of_player++) {
        if (player[num_of_player].have_shield_or_not() == NO) {
            player[num_of_player].draw_ships(window, "player.png");
        }
        else {
            player[num_of_player].draw_ships(window, "player_shield.png");
        }
    }
}

void Game::shoot_to_enemy(Window *window, vector <Ship> &enemy) {
    for (int num_of_enemy = 0; num_of_enemy < enemy.size(); num_of_enemy++) { 
        if (enemy[num_of_enemy].get_availability() == YES) {      
            for (int num_of_shot = 0; num_of_shot < player_shot.size(); num_of_shot++)  {
                if (player_shot[num_of_shot].get_availability() == YES) {
                    if (player_shot[num_of_shot].get_coordinate_of_row() <= 
                    enemy[num_of_enemy].get_coordinate_of_row()+SHIP_ROW_SCALE &&
                    player_shot[num_of_shot].get_coordinate_of_row()+SHOT_ROW_SCALE >= enemy[num_of_enemy].get_coordinate_of_row()) {
                        for (int width = enemy[num_of_enemy].get_coordinate_of_col(); 
                            width < enemy[num_of_enemy].get_coordinate_of_col()+SHIP_COL_SCALE; width++) {
                            if (player_shot[num_of_shot].get_coordinate_of_col() == width) {
                                enemy[num_of_enemy].set_availability(NO);
                                player_shot[num_of_shot].set_availability(NO);
                                create_power_up(enemy[num_of_enemy].get_coordinate_of_row(), 
                                enemy[num_of_enemy].get_coordinate_of_col());
                                num_of_unavailable_enemies += 1;
                                window->play_sound_effect("Death_Star_Explode_Sound_Effect.mp3");
                            }
                        } 
                    }
                }
            }  
        }      
    }
}

void Game::create_power_up(int row_of_destroyed_enemy, int col_of_destroyed_enemy) {
    int create_power = rand() % POSSIBILITIES_AFTER_ENEMY_DESTRUCTION;
    if (create_power == MAKE_POWER) {
        int which_power = rand() % POSSIBILITIES_AFTER_POWER_CREATION;
        if (which_power == SHIELD) {
            shield.push_back(PowerUp(row_of_destroyed_enemy, col_of_destroyed_enemy, SHIELD));
        }
        else if (which_power == INCREASE_SHOT_SPEED) {
            increase_shot_speed.push_back(PowerUp(row_of_destroyed_enemy, col_of_destroyed_enemy, INCREASE_SHOT_SPEED));
        }
    }
}

void Game::draw_power_up(Window *window, vector <PowerUp> &power_up, string filename) {
    for (int num_of_power = 0; num_of_power < power_up.size(); num_of_power++) {
        power_up[num_of_power].draw_power(window, filename);
    }
}

void Game::get_power_up(vector <PowerUp> &power_up) {
    for (int num_of_power = 0; num_of_power < power_up.size(); num_of_power++) {
        if (power_up[num_of_power].get_availability() == YES) {
            if (player[0].get_coordinate_of_row() <= power_up[num_of_power].get_coordinate_of_row()+SHIP_ROW_SCALE &&
                player[0].get_coordinate_of_row()+SHIP_ROW_SCALE >= power_up[num_of_power].get_coordinate_of_row() &&
                player[0].get_coordinate_of_col() <= power_up[num_of_power].get_coordinate_of_col()+SHIP_COL_SCALE &&
                player[0].get_coordinate_of_col()+SHIP_COL_SCALE >= power_up[num_of_power].get_coordinate_of_col()) {
                if (power_up[num_of_power].get_type_of_power() == SHIELD && player[0].have_shield_or_not() == NO) {
                    player[0].set_shield();
                    power_up[num_of_power].remove_availability();
                }
                if (power_up[num_of_power].get_type_of_power() == INCREASE_SHOT_SPEED && 
                    player[0].increased_shot_speed_or_not() == NO) {
                    player[0].set_increased_shot_speed();
                    power_up[num_of_power].remove_availability();
                }
                
            }
        }
    }
}

void Game::lose_power_up() {
    if (player[0].have_shield_or_not() == YES) {
        time_to_lose_shield += 1;
        if (time_to_lose_shield > TIME_TO_LOSE_SHIELD) {
            player[0].remove_shield();
            time_to_lose_shield = 0;
        }
    }
    if (player[0].increased_shot_speed_or_not() == YES) {
        time_to_lose_shot_speed += 1;
        if (time_to_lose_shot_speed >
            TIME_TO_LOSE_SHOT_SPEED) {
            player[0].remove_increased_shot_speed();
            time_to_lose_shot_speed = 0;
        }
    }
}

void Game::shoot_to_hostage() {
    for (int num_of_hostage = 0; num_of_hostage < hostage.size(); num_of_hostage++) {      
        for (int num_of_shot = 0; num_of_shot < player_shot.size(); num_of_shot++)  {
            if (player_shot[num_of_shot].get_availability() == YES) {
                if (player_shot[num_of_shot].get_coordinate_of_row() <= hostage[num_of_hostage].get_coordinate_of_row()+SHIP_ROW_SCALE &&
                player_shot[num_of_shot].get_coordinate_of_row()+SHOT_ROW_SCALE >= hostage[num_of_hostage].get_coordinate_of_row()) {
                    for (int width = hostage[num_of_hostage].get_coordinate_of_col(); 
                        width < hostage[num_of_hostage].get_coordinate_of_col()+SHIP_COL_SCALE; width++) {
                        if (player_shot[num_of_shot].get_coordinate_of_col() == width) {
                            player_lost = YES;
                        }
                    } 
                }
            }
        }       
    }
}

void Game::player_shooting(Window *window) {
    if (pressed_space_before == YES) {
        for (int num_of_shot = 0; num_of_shot < player_shot.size(); num_of_shot++) {
            player_shot[num_of_shot].draw_shot(window);
            if (player_shot[num_of_shot].get_shot_situation() == YES) {
                if (player[0].increased_shot_speed_or_not() == NO) {
                    player_shot[num_of_shot].move_regular_shot();
                }
                else {
                    player_shot[num_of_shot].move_powered_shot();
                }
            }
        }               
    }  
}

void Game::enemy_shooting(Window *window, vector <Ship> enemy, vector <Shot> &enemy_shot, int period_between_shots, int &time_to_shoot) {
    time_to_shoot += 1;
    if (time_to_shoot % period_between_shots == YES) {
        for (int num_of_enemy = 0; num_of_enemy < enemy.size(); num_of_enemy++) {
            if (enemy[num_of_enemy].get_availability() == YES) {
                enemy_shot.push_back(Shot(window, 
                enemy[num_of_enemy].get_coordinate_of_row()+SHIP_ROW_SCALE-SHOT_ROW_SCALE,
                enemy[num_of_enemy].get_coordinate_of_col()+(SHIP_COL_SCALE/2), ENEMY_SHOT));
            }
        }               
    }
    for (int num_of_shot = 0; num_of_shot < enemy_shot.size(); num_of_shot++) {
        enemy_shot[num_of_shot].draw_shot(window);
        enemy_shot[num_of_shot].move_regular_shot();
    } 
}

void Game::get_shot(vector <Shot> &enemy_shot) { 
    if (player[0].have_shield_or_not() == NO) {      
        for (int num_of_shot = 0; num_of_shot < enemy_shot.size(); num_of_shot++)  {
            if (enemy_shot[num_of_shot].get_availability() == YES) {
                if (enemy_shot[num_of_shot].get_coordinate_of_row() <= 
                player[0].get_coordinate_of_row()+SHIP_ROW_SCALE &&
                enemy_shot[num_of_shot].get_coordinate_of_row()+SHOT_ROW_SCALE >= player[0].get_coordinate_of_row()) {
                    for (int width = player[0].get_coordinate_of_col(); 
                        width < player[0].get_coordinate_of_col()+SHIP_COL_SCALE; width++) {
                        if (enemy_shot[num_of_shot].get_coordinate_of_col() == width) {
                            player_lost = YES;
                        }
                    } 
                }
            }
        } 
    }     
}

void Game::ships_collide(vector <Ship> ship) {
    for (int num_of_ship = 0; num_of_ship < ship.size(); num_of_ship++) {
        if (ship[num_of_ship].get_availability() == YES) {
            if (player[0].get_coordinate_of_row() <= ship[num_of_ship].get_coordinate_of_row()+SHIP_ROW_SCALE &&
                player[0].get_coordinate_of_row()+SHIP_ROW_SCALE >= ship[num_of_ship].get_coordinate_of_row() &&
                player[0].get_coordinate_of_col() <= ship[num_of_ship].get_coordinate_of_col()+SHIP_COL_SCALE &&
                player[0].get_coordinate_of_col()+SHIP_COL_SCALE >= ship[num_of_ship].get_coordinate_of_col()) {
                player_lost = YES;
            }
        }
    }
}

void Game::win_the_level() {
    if (immobile_enemy.size() + moving_enemy.size() == num_of_unavailable_enemies) {
        num_of_level += 1;
        level_is_started = NO;
        immobile_enemy.clear();
        moving_enemy.clear();
        hostage.clear();
        player.clear();
        player_shot.clear();
        immobile_enemy_shot.clear();
        moving_enemy_shot.clear();
        shield.clear();
        increase_shot_speed.clear();
    }
}

void Game::lose_the_game(Window *window) {
    window->clear();
    window->stop_music();
    immobile_enemy.clear();
    moving_enemy.clear();
    hostage.clear();
    player.clear();
    player_shot.clear();
    immobile_enemy_shot.clear();
    moving_enemy_shot.clear();
    shield.clear();
    increase_shot_speed.clear();
    window->draw_img("darthvader.jpg", Rectangle(0, 0, col*MAP_SCALE, row*MAP_SCALE));
    player_lost = YES;
    window->play_sound_effect("Darth-vader-breathing.wav"); 
}

void Game::win_the_game(Window *window) {
    window->clear();
    window->stop_music();
    immobile_enemy.clear();
    moving_enemy.clear();
    hostage.clear();
    player.clear();
    player_shot.clear();
    immobile_enemy_shot.clear();
    shield.clear();
    increase_shot_speed.clear();
    window->draw_img("luke-skywalker.jpg", Rectangle(0, 0, col*MAP_SCALE, row*MAP_SCALE));
    window->play_sound_effect("force.mp3");
}