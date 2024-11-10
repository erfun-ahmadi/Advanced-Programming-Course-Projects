#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

void getting_inputs(vector<int> &weights, int &target_weight) {
    int num_of_weights, new_weight;
    cin >> num_of_weights >>target_weight;
    for(int num_of_weight = 1; num_of_weight <= num_of_weights; num_of_weight++) {
        cin >> new_weight;
        weights.push_back(new_weight);
    }
}

void combination(vector<int> &weights, vector<int> &chosen_weights, int start, int end,
                     int num_of_chosen_weight, int amount_of_chosen_weights, int target_weight) {

    if(num_of_chosen_weight == amount_of_chosen_weights) {
        int sum_of_weights = 0;
        for(int j = 0; j < amount_of_chosen_weights; j++)
            sum_of_weights += chosen_weights[j];
        if(sum_of_weights == target_weight) {
            cout << "True" << endl;
            exit(0);
        }
        return;
    }
    for (int i = start; i <= end && end - i + 1 >= amount_of_chosen_weights - num_of_chosen_weight; i++) {
        chosen_weights[num_of_chosen_weight] = weights[i];
        combination(weights, chosen_weights, i+1, end, num_of_chosen_weight+1, 
                        amount_of_chosen_weights, target_weight);
    }
}

void whether_we_can_weigh(vector<int> &weights, int target_weight, int num_of_step) {
    int target_weight_2nd_edition = target_weight;
        for(int num_of_weight = 0; num_of_weight < weights.size(); num_of_weight++) {
            vector<int> weights_2nd_edition = weights;
            for(int amount_of_chosen_weights = num_of_weight; amount_of_chosen_weights <= weights.size(); amount_of_chosen_weights++) {
                vector<int> chosen_weights(amount_of_chosen_weights);
                combination(weights, chosen_weights, 0, weights.size(), 0, amount_of_chosen_weights, target_weight);
                if(amount_of_chosen_weights == weights.size()) {
                    target_weight += weights[num_of_weight];
                    weights_2nd_edition.erase(weights_2nd_edition.begin() + num_of_weight);
                    if(weights_2nd_edition.size() == 0) break;
                    else
                    whether_we_can_weigh(weights_2nd_edition, target_weight, num_of_step);
                }
            }
            target_weight = target_weight_2nd_edition;
        }  
}

int main() {
    int target_weight;
    vector<int> weights;
    getting_inputs(weights, target_weight);
    int num_of_weight = 0, num_of_step = 1;
    whether_we_can_weigh(weights, target_weight, num_of_step);
    cout << "False" << endl;
    return 0;
}