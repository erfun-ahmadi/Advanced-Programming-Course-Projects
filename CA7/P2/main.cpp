#include <iostream>
#include <iomanip>
#include "utaxi.h"
#include "get_commands.h"

using namespace std;

int main(int argc, char* argv[]) {
    Utaxi utaxi;
    cout << setprecision(2) << fixed;
    get_commands(utaxi, argv);
    return 0;
}