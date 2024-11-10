#include "Library.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	Library ut_lib;
	vector<string> titles;
	ut_lib.add_student_member("0", "std1");
	ut_lib.add_magazine("magazine1", 2010, 10, 2);
	ut_lib.borrow("std1", "magazine1");
	ut_lib.time_pass(1);
	ut_lib.extend("std1", "magazine1");
	return 0;
}