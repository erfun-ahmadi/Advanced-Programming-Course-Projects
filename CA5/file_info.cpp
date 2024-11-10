#include <fstream>
#include "file_info.h"
#include "game.h"

using namespace std;

void get_info_from_file(char *argv[]) {
    string each_line;
    vector <string> game_map;
    ifstream map_file(argv[1]);
    while(getline(map_file, each_line)) {
        game_map.push_back(each_line);
    }
    map_file.close();
    Game game(game_map);
}

