#include <iostream>
#include "utaxi.h"
#include "get_commands.h"

using namespace std;

int main(int argc, char* argv[]) {
    Utaxi utaxi;
    get_commands(utaxi, argv);
    return 0;
}