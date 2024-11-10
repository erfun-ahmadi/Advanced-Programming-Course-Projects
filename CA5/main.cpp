#include <time.h>
#include "rsdl.hpp"
#include "file_info.h"

using namespace std;

int main(int argc, char* argv[]) {
    srand(time(0));
    get_info_from_file(argv);
    return 0;
}


