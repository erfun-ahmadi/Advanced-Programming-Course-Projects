#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

const int minutes_per_hour = 60;
const string no_translator_found = "Not Found";

struct translator {
    string translator_name;
    string start_time;
    string end_time;
    vector<int> free_time_in_minute;
    vector<string> languages;
};

struct event {
    string event_name;
    string start_time;
    string end_time;
    vector<int> event_time_in_minute;
    vector<string> languages;
    vector<string> result;
};

typedef vector<translator> translators;
typedef vector<event> events;

void save_info_from_file(vector<string> &whole_info, char* argv[]) {
    string each_info;
    ifstream info_file(argv[1]);
    while (getline(info_file, each_info)) {
        whole_info.push_back(each_info);
    }
    info_file.close();
}

void save_translators_data(vector<string> &whole_info, translators &translators_info) {
    int num_of_translators = stoi(whole_info[0]);
    translators translators_tmp(num_of_translators);
    whole_info.erase(whole_info.begin());
    string space_delimiter = " ";
    for (int num_of_translator = 0; num_of_translator < num_of_translators; num_of_translator++) {
        int pos, num_of_info = 0;
        while ((pos = whole_info[0].find(space_delimiter)) != -1) {
            if (num_of_info == 0) {
                translators_tmp[num_of_translator].translator_name = whole_info[0].substr(0, pos);
            }
            else if (num_of_info == 1) {
                translators_tmp[num_of_translator].start_time = whole_info[0].substr(0, pos);
            }   
            else if (num_of_info == 2) {
                translators_tmp[num_of_translator].end_time = whole_info[0].substr(0, pos);
            }
            else if (num_of_info >= 3) {
                translators_tmp[num_of_translator].languages.push_back(whole_info[0].substr(0, pos));
            }   
            whole_info[0].erase(0, pos+space_delimiter.length());
            num_of_info += 1;
        }
        translators_tmp[num_of_translator].languages.push_back(whole_info[0]);
        whole_info.erase(whole_info.begin());
    }
    translators_info = translators_tmp;
}

void save_events_data(vector<string> &whole_info, events &events_info) {
    int num_of_events = stoi(whole_info[0]);
    events events_tmp(num_of_events);
    whole_info.erase(whole_info.begin());
    string space_delimiter = " ";
    for (int num_of_event = 0; num_of_event < num_of_events; num_of_event++) {
        int pos, num_of_info = 0;
        while ((pos = whole_info[0].find(space_delimiter)) != -1) {
            if (num_of_info == 0) {
                events_tmp[num_of_event].event_name = whole_info[0].substr(0, pos);
            }
            else if (num_of_info == 1) {
                events_tmp[num_of_event].start_time = whole_info[0].substr(0, pos);
            }   
            else if (num_of_info == 2) {
                events_tmp[num_of_event].end_time = whole_info[0].substr(0, pos);
            }   
            else if (num_of_info >= 3) {
                events_tmp[num_of_event].languages.push_back(whole_info[0].substr(0, pos));
            } 
            whole_info[0].erase(0, pos+space_delimiter.length());
            num_of_info += 1;
        }
        events_tmp[num_of_event].languages.push_back(whole_info[0]);
        whole_info.erase(whole_info.begin());
        for (int num_of_language = 0; num_of_language < events_tmp[num_of_event].languages.size(); num_of_language++) {
            events_tmp[num_of_event].result.push_back("0");
        }
    }
    events_info = events_tmp;
}

void turn_translator_free_time_into_minute(translators &translators_info) {
    for (int num_of_translator = 0; num_of_translator < translators_info.size(); num_of_translator++) {
        int start_hour = stoi(translators_info[num_of_translator].start_time.substr(0,2));
        int start_minute = stoi(translators_info[num_of_translator].start_time.substr(3,5));
        translators_info[num_of_translator].free_time_in_minute.push_back(start_hour * minutes_per_hour + start_minute);
        int end_hour = stoi(translators_info[num_of_translator].end_time.substr(0,2));
        int end_minute = stoi(translators_info[num_of_translator].end_time.substr(3,5));
        translators_info[num_of_translator].free_time_in_minute.push_back(end_hour * minutes_per_hour + end_minute);
    }
}

void turn_event_time_into_minute(events &events_info) {
    for (int num_of_event = 0; num_of_event < events_info.size(); num_of_event++) {
        int start_hour = stoi(events_info[num_of_event].start_time.substr(0,2));
        int start_minute = stoi(events_info[num_of_event].start_time.substr(3,5));
        events_info[num_of_event].event_time_in_minute.push_back(start_hour * minutes_per_hour + start_minute);
        int end_hour = stoi(events_info[num_of_event].end_time.substr(0,2));
        int end_minute = stoi(events_info[num_of_event].end_time.substr(3,5));
        events_info[num_of_event].event_time_in_minute.push_back(end_hour * minutes_per_hour + end_minute);
    }
}

int find_num_of_translators_for_each_language(events each_event, translators &translators_info) {
    int num_of_translators = 0, num_of_translators_tmp, index;
    for (int num_of_language = 0; num_of_language < each_event[0].languages.size(); num_of_language++) {  
        for (int num_of_translator = 0; num_of_translator < translators_info.size(); num_of_translator++) {
            for (int num_of_translators_language = 0; 
                 num_of_translators_language < translators_info[num_of_translator].languages.size(); num_of_translators_language++) {
                if (each_event[0].languages[num_of_language] == 
                    translators_info[num_of_translator].languages[num_of_translators_language]) {
                    num_of_translators += 1;
                    break;
                }
            }    
        }
        if (num_of_language == 0) {
            num_of_translators_tmp = num_of_translators;
            index = 0;
        }
        else {
            if (num_of_translators < num_of_translators_tmp) {
                num_of_translators_tmp = num_of_translators;
                index = num_of_language;
            }
        } 
        num_of_translators = 0;
    }
    return index;
}

void set_translator_for_event(events &each_event, translators &free_translator, int num_of_language_to_check,
                              translators &translators_info) {
    each_event[0].result[num_of_language_to_check] = free_translator[0].translator_name;
    for (int free_time = 0; free_time < free_translator[0].free_time_in_minute.size(); free_time++) {
        if (free_time % 2 == 0 && each_event[0].event_time_in_minute[0] >= 
            free_translator[0].free_time_in_minute[free_time] && each_event[0].event_time_in_minute[1] <=
            free_translator[0].free_time_in_minute[free_time+1]) {
            if (each_event[0].event_time_in_minute[0] == free_translator[0].free_time_in_minute[free_time]) {
                if (each_event[0].event_time_in_minute[1] == free_translator[0].free_time_in_minute[free_time+1]) {
                    free_translator[0].free_time_in_minute[free_time] = 0;
                    free_translator[0].free_time_in_minute[free_time+1] = 0; 
                    break;                     
                }
                else {
                    free_translator[0].free_time_in_minute[free_time] = each_event[0].event_time_in_minute[1];
                    break;
                }
            }
            else {
                if (each_event[0].event_time_in_minute[1] == free_translator[0].free_time_in_minute[free_time+1]) {
                   free_translator[0].free_time_in_minute[free_time+1] = each_event[0].event_time_in_minute[0];
                   break;
                }
                else {
                    free_translator[0].free_time_in_minute.push_back(0);
                    free_translator[0].free_time_in_minute.push_back(0);
                    for (int num_of_free_time = free_translator[0].free_time_in_minute.size()-1;
                         num_of_free_time > free_time+2; num_of_free_time--) {
                        free_translator[0].free_time_in_minute[num_of_free_time] = 
                        free_translator[0].free_time_in_minute[num_of_free_time-2];
                    }
                    free_translator[0].free_time_in_minute[free_time+1] = each_event[0].event_time_in_minute[0];
                    free_translator[0].free_time_in_minute[free_time+2] = each_event[0].event_time_in_minute[1];
                    break;
                }   
            }
        }
    }  
    for (int num_of_translator = 0; num_of_translator < translators_info.size(); num_of_translator++) {
        if (translators_info[num_of_translator].translator_name == free_translator[0].translator_name) {
            translators_info[num_of_translator] = free_translator[0];
            break;
        }
    }  
}

void sort_in_alphabetic_order(events &each_event, translators &free_translators, int num_of_language_to_check,
                              translators &translators_info) {
    translators chosen_free_translator;
    for (int i = 0; i < free_translators.size(); i++) {
        for (int j = i+1; j < free_translators.size(); j++) {
            if (free_translators[i].translator_name > free_translators[j].translator_name) {
                swap(free_translators[i], free_translators[j]);
            }
        }    
    }
    chosen_free_translator.push_back(free_translators[0]);
    set_translator_for_event(each_event, chosen_free_translator, num_of_language_to_check, translators_info);
}

void translator_with_less_languages(events &each_event, translators &free_translators, int num_of_language_to_check,
                                    translators &translators_info) {
    translators chosen_free_translator;
    vector<int> index_of_free_translator;
    int num_of_languages;
    for (int num_of_free_translator = 0; num_of_free_translator < free_translators.size(); num_of_free_translator++) {
        if (num_of_free_translator == 0) {
            index_of_free_translator.push_back(num_of_free_translator);
            num_of_languages = free_translators[num_of_free_translator].languages.size();
        }
        else {
            if (free_translators[num_of_free_translator].languages.size() < num_of_languages) {
                index_of_free_translator.erase(index_of_free_translator.begin(), index_of_free_translator.end());
                index_of_free_translator.push_back(num_of_free_translator);
                num_of_languages = free_translators[num_of_free_translator].languages.size();
            }
            else if (free_translators[num_of_free_translator].languages.size() == num_of_languages) {
                index_of_free_translator.push_back(num_of_free_translator);
            }
        }
    }
    for (int num_of_index = 0; num_of_index < index_of_free_translator.size(); num_of_index++) {
        chosen_free_translator.push_back(free_translators[index_of_free_translator[num_of_index]]);
    }
    if (index_of_free_translator.size() == 1) {
        set_translator_for_event(each_event, chosen_free_translator, num_of_language_to_check, translators_info);
    }
    else {
        sort_in_alphabetic_order(each_event, chosen_free_translator, num_of_language_to_check, translators_info);
    }
}

void find_free_translator(events &each_event, translators &translators_info, int num_of_language_to_check) {
    translators free_translators;
    for (int num_of_translator = 0; num_of_translator < translators_info.size(); num_of_translator++) {
        for (int num_of_language = 0; num_of_language < translators_info[num_of_translator].languages.size();
            num_of_language++) {
            if (translators_info[num_of_translator].languages[num_of_language] == 
                each_event[0].languages[num_of_language_to_check]) {
                for (int free_time = 0; free_time < translators_info[num_of_translator].free_time_in_minute.size(); free_time++) {
                    if (free_time % 2 == 0) {
                        if (translators_info[num_of_translator].free_time_in_minute[free_time] <= each_event[0].event_time_in_minute[0]
                            && translators_info[num_of_translator].free_time_in_minute[free_time+1] >=
                            each_event[0].event_time_in_minute[1]) {
                            free_translators.push_back(translators_info[num_of_translator]);
                        }
                    }
                    
                }
            }
        }
    }
    if (free_translators.size() == 0) {
        each_event[0].result[num_of_language_to_check] = no_translator_found;
    }
    else if (free_translators.size() == 1) {
        set_translator_for_event(each_event, free_translators, num_of_language_to_check, translators_info);
    }
    else if (free_translators.size() > 1) {
        translator_with_less_languages(each_event, free_translators, num_of_language_to_check, translators_info);
    }
}

void show_result(events each_event) {
    cout << each_event[0].event_name << endl;
    for (int num_of_language = 0; num_of_language < each_event[0].languages.size(); num_of_language++) {
        cout << each_event[0].languages[num_of_language] << ": " <<
        each_event[0].result[num_of_language] << endl;
    }   
}

void arrange_program(translators &translators_info, events &events_info) {
    int num_of_events = events_info.size();
    for (int num_of_event = 0; num_of_event < num_of_events; num_of_event++) {
        int num_of_each_events_language = events_info[num_of_event].languages.size(); 
        events each_event(1), each_event_2nd_edition(1);
        each_event[0] = events_info[num_of_event];      
        each_event_2nd_edition[0] = events_info[num_of_event];
        for (int num_of_language = 0; num_of_language < num_of_each_events_language; num_of_language++) {           
            int num_of_language_to_check = find_num_of_translators_for_each_language(each_event, translators_info);
            find_free_translator(each_event, translators_info, num_of_language_to_check);
            for (int i = 0; i < num_of_each_events_language; i++) {
                if (each_event_2nd_edition[0].languages[i] == 
                    each_event[0].languages[num_of_language_to_check]) {
                    each_event_2nd_edition[0].result[i] = 
                    each_event[0].result[num_of_language_to_check];
                }    
            }
            each_event[0].languages.erase(each_event[0].languages.begin()+num_of_language_to_check,
                                          each_event[0].languages.begin()+num_of_language_to_check+1);
            each_event[0].result.erase(each_event[0].result.begin()+num_of_language_to_check,
                                          each_event[0].result.begin()+num_of_language_to_check+1);
            if (num_of_language == num_of_each_events_language-1) {
                show_result(each_event_2nd_edition);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    translators translators_info;
    events events_info;
    vector<string> whole_info;
    save_info_from_file(whole_info, argv);
    save_translators_data(whole_info, translators_info);
    save_events_data(whole_info, events_info);
    turn_translator_free_time_into_minute(translators_info);
    turn_event_time_into_minute(events_info);
    arrange_program(translators_info, events_info);
    return 0;
}