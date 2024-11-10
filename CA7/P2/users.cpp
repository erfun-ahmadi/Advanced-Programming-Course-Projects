#include "users.h"

using namespace std;

User::User(string _username) {
    username = _username;
}

string User::get_username() {
    return username;
}

int User::get_trip_id() {
    return trip_id;
}