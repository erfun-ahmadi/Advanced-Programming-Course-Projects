#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

void getting_inputs(int &total_steps, int &num_of_number) {
    cin >> total_steps >> num_of_number;
}

void replacing_numbers(vector <int> &initiale_numbers_string, int total_steps, int num_of_number, int step) {
    vector<int> numbers_string_2nd_edition = initiale_numbers_string;  
    vector<vector<int> > replaced_numbers(pow(2,total_steps));
    if(step == total_steps-1) {
       cout << initiale_numbers_string[num_of_number-1] << endl;
    }
    else {
       initiale_numbers_string.clear();
       for(int j = 0; j < pow(2, step); j++) {
            if(numbers_string_2nd_edition[j] == 0) {
                replaced_numbers[j].push_back(0);
                replaced_numbers[j].push_back(1);            
                initiale_numbers_string.push_back(replaced_numbers[j][0]);
                initiale_numbers_string.push_back(replaced_numbers[j][1]);                
            }
            else if(numbers_string_2nd_edition[j] == 1) {
                replaced_numbers[j].push_back(1);
                replaced_numbers[j].push_back(0);            
                initiale_numbers_string.push_back(replaced_numbers[j][0]);
                initiale_numbers_string.push_back(replaced_numbers[j][1]);
            }
        }
        replacing_numbers(initiale_numbers_string, total_steps, num_of_number, step+1);
    }
}

int main() {
    vector<int> initiale_numbers_string = {0};
    int total_steps,num_of_number;
    int step = 0;
    getting_inputs(total_steps, num_of_number);
    replacing_numbers(initiale_numbers_string, total_steps, num_of_number, step);
    return 0;
}