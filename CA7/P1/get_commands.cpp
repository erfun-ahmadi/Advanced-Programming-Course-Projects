#include "get_commands.h"

using namespace std;

void get_commands(Utaxi utaxi, char* argv[]) {
    string each_command, each_line;
    while (getline(cin, each_line)) {
        utaxi.add_locations(argv);
        vector <string> commands;       
        stringstream line(each_line);
        while (getline(line, each_command, ' ')) {
            commands.push_back(each_command);
        }
        if (commands[0] == POST_COMMAND) {
            commands.erase(commands.begin(), commands.begin()+1);
            utaxi.post_command(commands);
        }
        else if (commands[0] == GET_COMMAND) {
            commands.erase(commands.begin(), commands.begin()+1);
            utaxi.get_command(commands);
        }
        else if (commands[0] == DELETE_COMMAND) {
            commands.erase(commands.begin(), commands.begin()+1);
            utaxi.delete_command(commands);
        }
        else {
            cout << BAD_REQUEST_ERROR << endl;
        }
        commands.clear();
    }
}