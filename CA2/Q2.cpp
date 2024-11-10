#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
using namespace std;

void getting_inputs(vector<char> &first_word, vector<char> &second_word, vector<char> &combination) {
	char new_letter;
	while ((new_letter = getchar()) != '\n') {
		first_word.push_back(new_letter);
	}
	while ((new_letter = getchar()) != '\n') {
		second_word.push_back(new_letter);
	}
	while ((new_letter = getchar()) != '\n') {
		combination.push_back(new_letter);
	}
}

void copy_vectors(vector<char> old_one, vector<char>& new_one)
{
	for (int i = 0; i < old_one.size(); i++)
		new_one.push_back(old_one[i]);
}

int whether_first_word_is_interleaving(vector<char> &first_word, vector<char> &combination,
	int size_of_first_word, int size_of_combination, int num_of_letter_com, int num_of_check) {
	if (num_of_check == size_of_first_word) return 1;
	else if (num_of_check != size_of_first_word && num_of_letter_com == combination.size()) return 0;
	else if (first_word[0] == combination[num_of_letter_com]) {
		first_word.erase(first_word.begin());
		combination.erase(combination.begin() + num_of_letter_com);
		whether_first_word_is_interleaving(first_word, combination, size_of_first_word, size_of_combination,
			num_of_letter_com, num_of_check + 1);
	}
	else if (first_word[0] != combination[num_of_letter_com]) {
		whether_first_word_is_interleaving(first_word, combination, size_of_first_word, size_of_combination,
			num_of_letter_com + 1, num_of_check);
	}
}

void show_results(int& check, int& is_interleaving, vector<char> &second_word, vector<char> &combination, vector<char>& combination2, vector<char>& second_word2, vector<char>& first_word2) {
	if (is_interleaving == 1) {
		for (int num_of_letter = 0; num_of_letter < combination.size(); num_of_letter++) {
			if (second_word[num_of_letter] != combination[num_of_letter]) {
				if (check == 0) {
					check = 1;
					int num_of_letter_1st = 0, num_of_letter_com = 0, num_of_check = 0;
					int size_of_first_word = first_word2.size(), size_of_combination = combination2.size();
					int is_interleaving = whether_first_word_is_interleaving(first_word2, combination2, size_of_first_word,
						size_of_combination, num_of_letter_com, num_of_check);
					show_results(check, is_interleaving, second_word2, combination2, combination, second_word, second_word);
					return;
				}
				else {
					cout << "Not Interleaving" << endl;
					break;
				}
			}
			else if (second_word[num_of_letter] == combination[num_of_letter] && num_of_letter == combination.size() - 1) {
				cout << "Interleaving" << endl;
			}
		}
	}
	else if (is_interleaving != 1) {
		cout << "Not Interleaving" << endl;
	}
}

int main() {
	vector<char> first_word, second_word, combination;
	vector<char> combination2, second_word2, first_word2;
	int num_of_letter_1st = 0, num_of_letter_com = 0, num_of_check = 0;
	getting_inputs(first_word, second_word, combination);
	copy_vectors(combination, combination2);
	copy_vectors(first_word, second_word2);
	copy_vectors(second_word, first_word2);
	int size_of_first_word = first_word.size(), size_of_combination = combination.size();
	int is_interleaving = whether_first_word_is_interleaving(first_word, combination, size_of_first_word,
		size_of_combination, num_of_letter_com, num_of_check);
	int check = 0;
	show_results(check, is_interleaving, second_word, combination, combination2, second_word2, first_word2);
	return 0;
}