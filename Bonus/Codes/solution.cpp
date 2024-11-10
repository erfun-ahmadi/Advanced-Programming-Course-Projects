#include <iostream>
#include <vector>
using namespace std;

vector<vector<int> > farm;
const int moves_each_day = 4;

void build_farm(int &num_of_rows, int &num_of_columns) {
    int product;
    cin >> num_of_rows >> num_of_columns;
    farm = vector < vector<int> > (num_of_rows, vector<int>(num_of_columns));
    for(int num_of_row = 0 ; num_of_row < num_of_rows ; num_of_row++){
        for(int num_of_column = 0 ; num_of_column < num_of_columns ; num_of_column++){
            cin >> product;
            farm[num_of_row][num_of_column] = product;
        }   
    }
}

long int calculate_sum(vector<int> each_row_or_column) {
    long int sum_of_products = 0;
    for (int index_of_product = 0; index_of_product < each_row_or_column.size(); index_of_product++)
    sum_of_products += each_row_or_column[index_of_product];
    return sum_of_products;
}

long int find_max_harvest_of_rows(int num_of_rows, int &chosen_row) {
    long int sum_of_products = 0;
    long int max_harvest_of_rows = 0;
    vector<long int> harvest_in_each_row;
    for(int num_of_row = 0; num_of_row < num_of_rows; num_of_row++){
        int sum_of_products = calculate_sum(farm[num_of_row]);
        harvest_in_each_row.push_back(sum_of_products);
    }
    for(int num_of_row_or_column = 0; num_of_row_or_column < num_of_rows; num_of_row_or_column++){
        if (harvest_in_each_row[num_of_row_or_column] > max_harvest_of_rows) {
            max_harvest_of_rows = harvest_in_each_row[num_of_row_or_column];
            chosen_row = num_of_row_or_column;
        }
    }
    return max_harvest_of_rows;
}

long int find_max_harvest_of_columns(int num_of_columns, int num_of_rows, int &chosen_column) {
    int sum_of_products = 0;
    long int max_harvest_of_columns = 0;
    for(int num_of_column = 0; num_of_column < num_of_columns; num_of_column++){
            for(int num_of_row = 0; num_of_row < num_of_rows; num_of_row++){
                sum_of_products += farm[num_of_row][num_of_column];
            }
            if(sum_of_products > max_harvest_of_columns){
                max_harvest_of_columns = sum_of_products;
                chosen_column = num_of_column;
            }
            sum_of_products = 0;
    }
    return max_harvest_of_columns;
}

void find_the_most_harvest_each_day(int max_harvest_of_rows, int max_harvest_of_columns, long int &most_harvest,
                                        int num_of_rows, int num_of_columns, int chosen_column, int chosen_row) {
    if(max_harvest_of_columns > max_harvest_of_rows){
        most_harvest += max_harvest_of_columns;
        for(int num_of_row = 0; num_of_row < num_of_rows; num_of_row++){
            farm[num_of_row][chosen_column] = 0;
        }
    }
    else{
        most_harvest += max_harvest_of_rows;
        for(int num_of_column = 0; num_of_column < num_of_columns; num_of_column++){
            farm[chosen_row][num_of_column] = 0;
        }
    }
}

void find_the_most_harvest(int num_of_rows, int num_of_columns, long int& most_harvest){    
    long int max_harvest_of_rows, max_harvest_of_columns;
    int chosen_row = 0;
    int chosen_column = 0;
    for(int move = 0; move < moves_each_day; move++) {
        max_harvest_of_rows = find_max_harvest_of_rows(num_of_rows, chosen_row);
        max_harvest_of_columns = find_max_harvest_of_columns(num_of_columns, num_of_rows, chosen_column);
        find_the_most_harvest_each_day(max_harvest_of_rows, max_harvest_of_columns, most_harvest, num_of_rows, num_of_columns,
                                       chosen_column, chosen_row);
    }
}

void show_the_most_harvest(long int most_harvest) {
    cout << most_harvest << endl;
}

int main() {
    int num_of_rows = 0, num_of_columns = 0;   
    long int most_harvest = 0;   
    build_farm(num_of_rows, num_of_columns);
    find_the_most_harvest(num_of_rows, num_of_columns, most_harvest);
    show_the_most_harvest(most_harvest);
    return 0;
} 