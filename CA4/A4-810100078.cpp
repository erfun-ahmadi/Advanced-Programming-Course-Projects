#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int INITIAL_MONEY = 1000;
const int MAX_MONEY = 10000;
const int INITIAL_HEALTH = 100;
const int HEAVY_COST = 3000;
const int PISTOL_COST = 400;
const int HEAVY_DAMAGE = 45;
const int PISTOL_DAMAGE = 20;
const int KNIFE_DAMAGE = 35;
const int HEAVY_BONUS = 100;
const int PISTOL_BONUS = 200;
const int KNIFE_BONUS = 500;
const int WINNING_BONUS = 2700;
const int LOSING_BONUS = 2400;
const int BEING_AFK = 1;
const int NOT_BEING_AFK = 0;
const int NOT_BEING_STARTED = 0;
const int BEING_STARTED = 1;

class Player {
public:
    string username;
    int money = INITIAL_MONEY;
    int health = INITIAL_HEALTH;
    vector<string> weapons = {"knife"};
    int round_kills = 0;
    int round_death = 0;
    int total_kills = 0;
    int total_deaths = 0;
    int is_afk = NOT_BEING_AFK;
    Player(string _username);
    void go_afk();
    void go_atk();
};

Player::Player(string _username) {
        username = _username;
    }

void Player::go_afk() {
        is_afk += BEING_AFK;
    }

void Player::go_atk() {
        is_afk = NOT_BEING_AFK;
    }        

class Game {
private:
    vector<Player> terrorist;
    vector<Player> counter_terrorist;
    vector<string> command;

public:
    void start();
    void add_user(string username, string team);
    void get_money(string username);
    void get_health(string username);
    void go_afk(string username);
    void go_atk(string username);
    void apply_buying_effects(Player &team, string weapon, int weapon_cost);
    void check_buying_conditions(string username, string weapon, Player &team);
    void buy(string username, string weapon);
    void aplly_shooting_effects(Player &attacker, Player &attacked, int weapon_damage, int weapon_bonus);
    void check_shooting_conditions(string weapon, Player &attacker, Player &attacked);
    void find_attacker_and_attacked(vector<Player> &team1, vector<Player> &team2, string attacker, string attacked, string weapon,
                                    int &num_of_check);
    void shoot(string attacker, string attacked, string weapon);
    void sort_teams_players(vector<Player> &team);
    void score_board();
    int find_num_of_dead_in_each_team(vector<Player> team);
    int find_num_of_afk_counters();
    void reset_death_kill();
    void reset_money(vector<Player> &winner, vector<Player> &loser);
    void reset_health();
    void reset_loser_weapons(vector<Player> &loser);
    void reset_information_for_new_round();
    void show_winner();
};

void Game::start() {
        cout << "fight!" << endl; 
    }

void Game::add_user(string username, string team) {
        if (team == "terrorist") {
            terrorist.push_back(Player(username));
        }
        else if (team == "counter-terrorist") {
            counter_terrorist.push_back(Player(username));
        }
        cout << "ok" << endl;
    }

void Game::get_money(string username) {
        for (int num_of_terror = 0; num_of_terror < terrorist.size(); num_of_terror++) {
            if (terrorist[num_of_terror].username == username) {
                cout << terrorist[num_of_terror].money << endl;
                return;
            }
        }
        for (int num_of_counter = 0; num_of_counter < counter_terrorist.size(); num_of_counter++) {
            if (counter_terrorist[num_of_counter].username == username)
            {
                cout << counter_terrorist[num_of_counter].money << endl;
                return;
            }
        }
    }

void Game::go_afk(string username) {
        for (int num_of_terror = 0; num_of_terror < terrorist.size(); num_of_terror++) {
            if (terrorist[num_of_terror].username == username) {
                terrorist[num_of_terror].go_afk();
                cout << "ok" << endl;
                return;
            }
        }
        for (int num_of_counter = 0; num_of_counter < counter_terrorist.size(); num_of_counter++) {
            if (counter_terrorist[num_of_counter].username == username) {
                counter_terrorist[num_of_counter].go_afk();
                cout << "ok" << endl;
                return;
            }
        }
    }      

void Game::get_health(string username) {
        for (int num_of_terror = 0; num_of_terror < terrorist.size(); num_of_terror++) {
            if (terrorist[num_of_terror].username == username) {
                cout << terrorist[num_of_terror].health << endl;
                return;
            }
        }
        for (int num_of_counter = 0; num_of_counter < counter_terrorist.size(); num_of_counter++) {
            if (counter_terrorist[num_of_counter].username == username) {
                cout << counter_terrorist[num_of_counter].health << endl;
                return;
            }
        }
    }   

void Game::go_atk(string username) {
        for (int num_of_terror = 0; num_of_terror < terrorist.size(); num_of_terror++) {
            if (terrorist[num_of_terror].username == username) {
                terrorist[num_of_terror].go_atk();
                cout << "ok" << endl;
                return;
            }
        }
        for (int num_of_counter = 0; num_of_counter < counter_terrorist.size(); num_of_counter++) {
            if (counter_terrorist[num_of_counter].username == username) {
                counter_terrorist[num_of_counter].go_atk();
                cout << "ok" << endl;
                return;
            }
        }
    }

void Game::apply_buying_effects(Player &team, string weapon, int weapon_cost) {
        if (team.money < weapon_cost) {
            cout << "insufficient money" << endl;
            return;
        }
        else {
            team.money -= weapon_cost;
            team.weapons.push_back(weapon);
            cout << "weapon bought successfully" << endl;
            return;
        }
    } 

void Game::check_buying_conditions(string username, string weapon, Player &team) {
        if (team.is_afk == BEING_AFK) {
            cout << "user not available" << endl;
            return;
        }
        else if (weapon != "heavy" && weapon != "pistol" && weapon != "knife") {
            cout << "weapon not available" << endl;
            return;
        }
        else if (weapon == "heavy" || weapon == "pistol" || weapon == "knife") {
            for (int num_of_weapon = 0; num_of_weapon < team.weapons.size(); num_of_weapon++) {
                if (weapon == team.weapons[num_of_weapon]) {
                    cout << "you already have this weapon" << endl;
                    return;
                }
                else {
                    if (num_of_weapon == team.weapons.size() - 1) {
                        if (weapon == "heavy") {
                            apply_buying_effects(team, weapon, HEAVY_COST);
                            return;
                        }
                        else if (weapon == "pistol") {
                            apply_buying_effects(team, weapon, PISTOL_COST);
                            return;
                        }
                    }
                }
            }
        }
    }  

void Game::buy(string username, string weapon) {
        for (int num_of_terror = 0; num_of_terror < terrorist.size(); num_of_terror++) {
            if (terrorist[num_of_terror].username == username) {
                check_buying_conditions(username, weapon, terrorist[num_of_terror]);
                return;
            }
            else {
                if (num_of_terror == terrorist.size() - 1) {
                    for (int num_of_counter = 0; num_of_counter < counter_terrorist.size(); num_of_counter++) {
                        if (counter_terrorist[num_of_counter].username == username) {
                            check_buying_conditions(username, weapon, counter_terrorist[num_of_counter]);
                            return;
                        }
                        else {
                            if (num_of_counter == counter_terrorist.size() - 1) {
                                cout << "user not available" << endl;
                                return;
                            }
                        }
                    }
                }
            }
        }
    }

void Game::aplly_shooting_effects(Player &attacker, Player &attacked, int weapon_damage, int weapon_bonus) {
        attacked.health -= weapon_damage;
        if (attacked.health <= 0) {
            attacked.health = 0;
            attacked.round_death += 1;
            attacker.round_kills += 1;
            attacked.total_deaths += 1;
            attacker.total_kills += 1;
            attacker.money += weapon_bonus;
        }
    }    

void Game::check_shooting_conditions(string weapon, Player &attacker, Player &attacked) {
        if (attacker.is_afk == BEING_AFK || attacked.is_afk == BEING_AFK) {
            cout << "user not available" << endl;
            return;
        }
        else if (attacker.health == 0) {
            cout << "attacker is dead" << endl;
            return;
        }
        else if (attacked.health == 0) {
            cout << "attacked is dead" << endl;
            return;
        }
        else if (weapon != "knife") {
            for (int num_of_weapon = 0; num_of_weapon < attacker.weapons.size(); num_of_weapon++) {
                if (attacker.weapons[num_of_weapon] == weapon)  { 
                    if (attacker.weapons[num_of_weapon] == "heavy") {
                        aplly_shooting_effects(attacker, attacked, HEAVY_DAMAGE, HEAVY_BONUS);
                    }
                    else if (attacker.weapons[num_of_weapon] == "pistol") {
                        aplly_shooting_effects(attacker, attacked, PISTOL_DAMAGE, PISTOL_BONUS);   
                    }
                    cout << "nice shot" << endl;    
                    return;               
                }
                else  {
                    if (num_of_weapon == attacker.weapons.size()-1) {
                        cout << "attacker doesn't have this gun" << endl;
                        return;
                    }
                }
            }
        }
        else if (weapon == "knife") {
            aplly_shooting_effects(attacker, attacked, KNIFE_DAMAGE, KNIFE_BONUS);    
            cout << "nice shot" << endl;    
            return; 
        }
    }    

void Game::find_attacker_and_attacked(vector<Player> &team1, vector<Player> &team2, string attacker, string attacked, string weapon,
                                    int &num_of_check) {
        for (int num_of_player1 = 0; num_of_player1 < team1.size(); num_of_player1++) {
            if (team1[num_of_player1].username == attacker) {
                for (int num_of_player2 = 0; num_of_player2 < team2.size(); num_of_player2++) {
                    if (team2[num_of_player2].username == attacked) {
                        check_shooting_conditions(weapon, team1[num_of_player1], team2[num_of_player2]);
                        return;
                    }
                    else {
                        if (num_of_player2 == team2.size()-1) {
                            for (int num_of_player1 = 0; num_of_player1 < team1.size(); num_of_player1++) {
                                if (team1[num_of_player1].username == attacked) {
                                    cout << "you can't shoot this player" << endl;
                                    return;
                                }
                                else {
                                    if (num_of_player1 == team1.size()-1) {
                                        cout << "user not available" << endl;
                                        return;
                                    }
                                }
                            }                            
                        }
                    }                    
                }               
            }
            else {
                if (num_of_player1 == team1.size()-1) {
                    num_of_check += 1;
                }
            }
        }
    }

void Game::shoot(string attacker, string attacked, string weapon) {
        int num_of_check = 0;
        find_attacker_and_attacked(terrorist, counter_terrorist, attacker, attacked, weapon, num_of_check);
        if (num_of_check == 1) {
            find_attacker_and_attacked(counter_terrorist, terrorist, attacker, attacked, weapon, num_of_check); 
        }    
        if (num_of_check == 2) {
            cout << "user not available" << endl; 
        }         
    }

void Game::sort_teams_players(vector<Player> &team) {
        for (int i = 0; i < team.size(); i++) {
            for (int j = i+1; j < team.size(); j++) {
                if(team[i].total_kills < team[j].total_kills) {
                    swap(team[i], team[j]);
                }
                if(team[i].total_deaths > team[j].total_deaths && team[i].total_kills == team[j].total_kills) {
                    swap(team[i], team[j]);
                }
                if(team[i].username > team[j].username && team[i].total_deaths == team[j].total_deaths && team[i].total_kills == team[j].total_kills) {
                    swap(team[i], team[j]);
                }
            }
        }
        for (int num_of_player = 0; num_of_player < team.size(); num_of_player++) {
            cout << team[num_of_player].username << " " << team[num_of_player].total_kills << " " << team[num_of_player].total_deaths << endl;
        }
    }  

void Game::score_board() {
        cout << "counter-terrorist players:" << endl;
        sort_teams_players(counter_terrorist);
        cout << "terrorist players:" << endl;
        sort_teams_players(terrorist);
    }  

int Game::find_num_of_dead_in_each_team(vector<Player> team) {
        int num_of_dead_in_team = 0;
        for (int num_of_player = 0; num_of_player < team.size(); num_of_player++) {
            if (team[num_of_player].round_death == 1) {
                num_of_dead_in_team += 1;
            }
        }
        return num_of_dead_in_team;
    }

int Game::find_num_of_afk_counters() {
    int num_of_afk_counters = 0;
    for (int num_of_counter = 0; num_of_counter < counter_terrorist.size(); num_of_counter++) {
        if (counter_terrorist[num_of_counter].is_afk == BEING_AFK) {
            num_of_afk_counters += 1;
        }
    }
    return num_of_afk_counters;
} 

void Game::reset_death_kill() {
        for (int num_of_terrors = 0; num_of_terrors < terrorist.size(); num_of_terrors++) {
            terrorist[num_of_terrors].round_kills = 0;
            terrorist[num_of_terrors].round_death = 0;
        }
        for (int num_of_counters = 0; num_of_counters < counter_terrorist.size(); num_of_counters++) {
            counter_terrorist[num_of_counters].round_kills = 0;
            counter_terrorist[num_of_counters].round_death = 0;
        }
    }

void Game::reset_money(vector<Player> &winner, vector<Player> &loser) {
        for (int num_of_winner = 0; num_of_winner < winner.size(); num_of_winner++) {
            winner[num_of_winner].money += WINNING_BONUS; 
            if (winner[num_of_winner].money > MAX_MONEY) {
                winner[num_of_winner].money = MAX_MONEY;
            }
        }
        for (int num_of_loser = 0; num_of_loser < loser.size(); num_of_loser++) {
            loser[num_of_loser].money += LOSING_BONUS;
            if (loser[num_of_loser].money > MAX_MONEY) {
                loser[num_of_loser].money = MAX_MONEY;
            }
        }
    } 

void Game::reset_health() {
        for (int num_of_terrors = 0; num_of_terrors < terrorist.size(); num_of_terrors++) {
            terrorist[num_of_terrors].health = INITIAL_HEALTH;
        }
        for (int num_of_counters = 0; num_of_counters < counter_terrorist.size(); num_of_counters++) {
            counter_terrorist[num_of_counters].health = INITIAL_HEALTH;
        }
    }

void Game::reset_loser_weapons(vector<Player> &loser) {
        for (int num_of_loser = 0; num_of_loser < loser.size(); num_of_loser++) {
            loser[num_of_loser].weapons.erase(loser[num_of_loser].weapons.begin(), 
                                              loser[num_of_loser].weapons.end());
            loser[num_of_loser].weapons.push_back("knife");
        }
    } 

void Game::reset_information_for_new_round() {
        reset_death_kill();
        reset_health();
    }

void Game::show_winner() {
        int num_of_dead_terrors = find_num_of_dead_in_each_team(terrorist);
        int num_of_dead_counters = find_num_of_dead_in_each_team(counter_terrorist);
        int num_of_afk_counters = find_num_of_afk_counters();
        if (num_of_dead_terrors == terrorist.size()) {
            cout << "counter-terrorist won" << endl;
            reset_money(counter_terrorist, terrorist);
            reset_loser_weapons(terrorist);
        }
        else if (num_of_dead_counters == counter_terrorist.size()) {
            cout << "terrorist won" << endl;
            reset_money(terrorist, counter_terrorist);
            reset_loser_weapons(counter_terrorist);
        }
        else if (num_of_dead_terrors < terrorist.size() && num_of_dead_counters < counter_terrorist.size()) {
            if (num_of_afk_counters + num_of_dead_counters == counter_terrorist.size()) {
                cout << "terrorist won" << endl;
                reset_money(terrorist, counter_terrorist);
                reset_loser_weapons(counter_terrorist);
            }
            else {
                cout << "counter-terrorist won" << endl;
                reset_money(counter_terrorist, terrorist);
                reset_loser_weapons(terrorist);
            }
        }
        reset_information_for_new_round();
    }                  


class Commands {
private:
    int is_started = NOT_BEING_STARTED;
    string command;
    Game cs_go;
public:
    void add_user();
    void score_board();
    void get_commands();
    void show_winner();
};

void Commands::add_user() {
        string username, team;
        cin >> username >> team;
        if (is_started == NOT_BEING_STARTED)
        {
            cs_go.add_user(username, team);
        }
    }

void Commands::score_board() {
        cs_go.score_board();
    } 

void Commands::get_commands() {
        cin >> command;
        if (command == "start") {
            cs_go.start();
            is_started += BEING_STARTED;
        }
        if (command == "get-money") {
            string username;
            cin >> username;
            cs_go.get_money(username);
        }    
        if (command == "get-health") {
            string username;
            cin >> username;
            cs_go.get_health(username);
        }
        if (command == "go-afk") {
            string username;
            cin >> username;
            cs_go.go_afk(username);
        }
        if (command == "go-atk") {
            string username;
            cin >> username;
            cs_go.go_atk(username);
        }
        if (command == "buy") {
            string username, weapon;
            cin >> username >> weapon;
            if (is_started == BEING_STARTED) {
                cout << "you can't buy weapons anymore" << endl;
            }
            else {
                cs_go.buy(username, weapon);
            }
        }
        if (command == "shoot") {
            string attacker, attacked, weapon;
            cin >> attacker >> attacked >> weapon;
            if (!is_started) {
                cout << "the game hasn't started yet" << endl;
            }
            else {
                cs_go.shoot(attacker, attacked, weapon);
            }           
        }
        if (command == "score-board") {
            cs_go.score_board();
        }        
    }

void Commands::show_winner() {
        cs_go.show_winner();
        is_started = NOT_BEING_STARTED;
    }           

void game_process(Commands cmds) {
    int num_of_rounds, num_of_round = 0;
    cin >> num_of_rounds;
    int num_of_commands;
    string first_command;
    while (cin >> first_command) {      
        if (first_command == "add-user") {
            cmds.add_user();
        }
        else if (first_command == "score-board") {
            cmds.score_board();
        }
        else if (first_command == "round") {
            cin >> num_of_commands;
            int num_of_command = 0;
            while (num_of_command < num_of_commands) {
                cmds.get_commands();           
                num_of_command += 1;
            }
            cmds.show_winner();
        }
    } 
}

int main() {
    Commands cmds;
    game_process(cmds);
    return 0;   
}
