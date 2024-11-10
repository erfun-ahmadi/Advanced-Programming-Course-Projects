#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int possible_moves = 4;
int row_move[possible_moves] = {1, -1, 0, 0};
int col_move[possible_moves] = {0, 0, 1, -1};
const char rock = '#';
const char empty_space = '.';
const char bamboo = '*';

void draw_map(vector<string> &map) {
    string place;
    while(cin >> place) {
       map.push_back(place);     
    }   
}

void switch_map(vector<string > map, vector<vector<int> > &alternative_map) {
    vector<int> alternative_map_1st_d;
    for(int line = 0; line < map.size(); line++) {
        string elements = map[line];
        for(int num_of_element = 0; num_of_element < elements.size(); num_of_element++) {
            if(elements[num_of_element] == empty_space) {
                alternative_map_1st_d.push_back(0);
            }
            else if(elements[num_of_element] == rock) {
                alternative_map_1st_d.push_back(-1);
            }
            if(elements[num_of_element] == bamboo) {
                alternative_map_1st_d.push_back(-10);
            }
        }
        alternative_map.push_back(alternative_map_1st_d);
        alternative_map_1st_d.clear();
    }
}

void finding_the_shortest_path(vector<vector<int>> alternative_map, vector<int> &len_of_path, int row,
                               int col, int num_of_moves) {
    if(row == 0 && col == 0) {
        if(alternative_map[row][col+1] == 0 && alternative_map[row][col+1] != num_of_moves-1 &&
           col != alternative_map[row].size()-1) {
            col += 1;
            num_of_moves += 1; 
            alternative_map[row][col] = num_of_moves; 
        }
        else if(alternative_map[row])
    }    
}

int main() {
    vector <string > map;
    vector <vector<int> > alternative_map;
    vector<int> len_of_path; 
    int num_of_moves = 0;  
    draw_map(map);
    switch_map(map, alternative_map);
    finding_the_shortest_path(alternative_map, len_of_path, 0, 0, num_of_moves);
}