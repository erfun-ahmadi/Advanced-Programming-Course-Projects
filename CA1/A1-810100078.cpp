#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <iomanip>
using namespace std;

const int beginning_of_day = 12;
const int last_minute_of_day = 480;
const int minutes_per_hour = 60;

void scan_event_times(vector< vector<string> > &event_time) {
    char input_hour, input_minute;
    vector <string> event_time_1st_d;
    char event_start_hour[2], event_start_minute[2], event_end_hour[2], event_end_minute[2];
    int num_of_event = 0;
    while(true) {
        int num_of_char = 0;
        while((input_hour = getchar()) != ':') {
            event_start_hour[num_of_char] = input_hour; 
            if(input_hour == '#') break;   
            num_of_char++;    
        }
        if(event_start_hour[0] == '#') break;
        event_start_hour[num_of_char] = NULL;
        event_time_1st_d.push_back(event_start_hour);
        event_time.push_back(event_time_1st_d);
        event_time_1st_d.clear();
        num_of_char = 0;

        while((input_minute = getchar()) != '-') {
            event_start_minute[num_of_char] = input_minute;
            num_of_char++;
        }
        event_start_minute[num_of_char] = NULL;
        event_time[num_of_event].push_back(event_start_minute);
        num_of_char = 0;

        while((input_hour = getchar()) != ':') {
            event_end_hour[num_of_char] = input_hour;    
            num_of_char++;    
        }
        event_end_hour[num_of_char] = NULL;
        event_time[num_of_event].push_back(event_end_hour);
        num_of_char = 0;

        while((input_minute = getchar()) != '\n') {
            event_end_minute[num_of_char] = input_minute;
            num_of_char++;
        }
        event_end_minute[num_of_char] = NULL;
        event_time[num_of_event].push_back(event_end_minute);

        num_of_event++;
    }
}

void scan_tasks(vector< vector<string> > &tasks) {
    char input_duration, input_range;
    vector <string> tasks_1st_d;
    char duration[3], range[2];
    int num_of_task = 0;
    char skip_Enter = getchar();
    char check_Ctrl_D;
    while(cin >> check_Ctrl_D) {
        duration[0] = check_Ctrl_D;
        int duration_num_of_char = 1;
        int range_num_of_char = 0;
        while((input_duration = getchar()) != ' ') {
            duration[duration_num_of_char] = input_duration;
            duration_num_of_char++;
        }
        duration[duration_num_of_char] = NULL;
        tasks_1st_d.push_back(duration);
        tasks.push_back(tasks_1st_d);
        tasks_1st_d.clear();

        while((input_range = getchar()) != '\n') {
            range[range_num_of_char] = input_range;
            range_num_of_char++;
        }
        range[range_num_of_char] = NULL;
        tasks[num_of_task].push_back(range);

        num_of_task++;
    }
}

void hour_to_minute(vector< vector<string> > &event_time, vector< vector<string> > &tasks,
                    vector< vector<string> > &event_time_in_minute) {
    string start_minute, end_minute;   
    vector<string> event_time_in_minute_1st_d;          
    for(int num_of_event = 0; num_of_event < event_time.size(); num_of_event++) {
        int first_hour = stoi(event_time[num_of_event][0]);
        int first_minute = stoi(event_time[num_of_event][1]);
        int last_hour = stoi(event_time[num_of_event][2]);
        int last_minute = stoi(event_time[num_of_event][3]);
        int start_minute_int = (first_hour - beginning_of_day)*minutes_per_hour + first_minute;
        int end_minute_int = (last_hour - beginning_of_day)*minutes_per_hour + last_minute;
        start_minute = to_string(start_minute_int);
        end_minute = to_string(end_minute_int);
        event_time_in_minute_1st_d.push_back(start_minute);
        event_time_in_minute_1st_d.push_back(end_minute);
        event_time_in_minute.push_back(event_time_in_minute_1st_d);
        event_time_in_minute_1st_d.clear();
    }
}

void from_12_before_20(vector< vector<string> > &event_time_in_minute, vector< vector<string> > &empty_time,
                       vector<string> &empty_time_1st_d, int num_of_event) {
    if(num_of_event != event_time_in_minute.size()-1) {
       if(stoi(event_time_in_minute[num_of_event][1]) != stoi(event_time_in_minute[num_of_event+1][0])) {
           empty_time_1st_d.push_back(event_time_in_minute[num_of_event][1]);
           empty_time_1st_d.push_back(event_time_in_minute[num_of_event+1][0]);
           empty_time.push_back(empty_time_1st_d);
           empty_time_1st_d.clear();
        }   
    }
    else if(num_of_event == event_time_in_minute.size()-1) {
        empty_time_1st_d.push_back(event_time_in_minute[num_of_event][1]);
        empty_time_1st_d.push_back(to_string(last_minute_of_day));
        empty_time.push_back(empty_time_1st_d);
        empty_time_1st_d.clear();
    }
}

void after_12_until_20(vector< vector<string> > &event_time_in_minute, vector< vector<string> > &empty_time,
                       vector<string> &empty_time_1st_d, int num_of_event) { 
    if(num_of_event == 0) {  
      empty_time_1st_d.push_back(to_string(0));
      empty_time_1st_d.push_back(event_time_in_minute[num_of_event][0]);
      empty_time.push_back(empty_time_1st_d);
      empty_time_1st_d.clear();          
    }
    else {
      empty_time_1st_d.push_back(event_time_in_minute[num_of_event-1][1]);
      empty_time_1st_d.push_back(event_time_in_minute[num_of_event][0]);
      empty_time.push_back(empty_time_1st_d);
      empty_time_1st_d.clear();
    }
}

void after_12_before_20(vector< vector<string> > &event_time_in_minute, vector< vector<string> > &empty_time,
                       vector<string> &empty_time_1st_d, int num_of_event) { 
    if(num_of_event == 0) {
        empty_time_1st_d.push_back(to_string(0));
        empty_time_1st_d.push_back(event_time_in_minute[num_of_event][0]);
        empty_time.push_back(empty_time_1st_d);
        empty_time_1st_d.clear();      
    }
    else if((num_of_event != 0) && (num_of_event != event_time_in_minute.size())) {
        empty_time_1st_d.push_back(event_time_in_minute[num_of_event-1][1]);
        empty_time_1st_d.push_back(event_time_in_minute[num_of_event][0]);
        empty_time.push_back(empty_time_1st_d);
        empty_time_1st_d.clear();
    }
    else if(num_of_event == event_time_in_minute.size()) {
        empty_time_1st_d.push_back(event_time_in_minute[num_of_event-1][1]);
        empty_time_1st_d.push_back(to_string(last_minute_of_day));
        empty_time.push_back(empty_time_1st_d);
        empty_time_1st_d.clear();
    }
 }

void from_12_until_20(vector< vector<string> > &event_time_in_minute, vector< vector<string> > &empty_time,
                      vector<string> &empty_time_1st_d, int num_of_event) {
    empty_time_1st_d.push_back(event_time_in_minute[num_of_event][1]);
    empty_time_1st_d.push_back(event_time_in_minute[num_of_event+1][0]);
    empty_time.push_back(empty_time_1st_d);
    empty_time_1st_d.clear();
}

void arrange_empty_times(vector< vector<string> > &event_time_in_minute, vector< vector<string> > &empty_time) {
    vector<string> empty_time_1st_d;
    if((stoi(event_time_in_minute[0][0]) == 0 && 
        stoi(event_time_in_minute[event_time_in_minute.size()-1][1]) != last_minute_of_day) ||
       (stoi(event_time_in_minute[0][0]) != 0 && 
        stoi(event_time_in_minute[event_time_in_minute.size()-1][1]) == last_minute_of_day)) {
           for(int num_of_event = 0; num_of_event < event_time_in_minute.size(); num_of_event++) {
               if(stoi(event_time_in_minute[0][0]) == 0 && 
                  stoi(event_time_in_minute[event_time_in_minute.size()-1][1]) != last_minute_of_day) {
                  from_12_before_20(event_time_in_minute, empty_time,empty_time_1st_d, num_of_event);
                }
               else if(stoi(event_time_in_minute[0][0]) != 0 && 
                       stoi(event_time_in_minute[event_time_in_minute.size()-1][1]) == last_minute_of_day) {
                   after_12_until_20(event_time_in_minute, empty_time,empty_time_1st_d, num_of_event);
                }
        }
    }
    else if(stoi(event_time_in_minute[0][0]) != 0 && 
            stoi(event_time_in_minute[event_time_in_minute.size()-1][1]) != last_minute_of_day) {
            for(int num_of_event = 0; num_of_event <= event_time_in_minute.size(); num_of_event++) {
                after_12_before_20(event_time_in_minute, empty_time,empty_time_1st_d, num_of_event);
            }
    }
    else if(stoi(event_time_in_minute[0][0]) == 0 && 
            stoi(event_time_in_minute[event_time_in_minute.size()-1][1]) == last_minute_of_day) {
            for(int num_of_event = 0; num_of_event < event_time_in_minute.size()-1; num_of_event++) {
                from_12_until_20(event_time_in_minute, empty_time,empty_time_1st_d, num_of_event);
            }
    }
    for(int i = 0; i < empty_time.size(); i++) {
        if(empty_time[i][0] == empty_time[i][1]) {
            empty_time.erase(empty_time.begin()+i);
        }
    }  
}

void put_tasks_in_empty_times(vector< vector<string> > &tasks, vector< vector<string> > &empty_time,
                              vector< vector<string> > &arranged_tasks) {
    vector<string> arranged_task_1st_d;
                                  
    for(int num_of_task = 0; num_of_task < tasks.size(); num_of_task++) {
        for(int num_of_empty_time = 0; num_of_empty_time < empty_time.size(); num_of_empty_time++) {
            if(stoi(tasks[num_of_task][1]) == num_of_empty_time+1) {
               arranged_task_1st_d.push_back(empty_time[num_of_empty_time][0]);
               arranged_task_1st_d.push_back(to_string(stoi(empty_time[num_of_empty_time][0])+stoi(tasks[num_of_task][0])));
               arranged_tasks.push_back(arranged_task_1st_d);
               arranged_task_1st_d.clear();
               int updated_time = stoi(empty_time[num_of_empty_time][0]);
               updated_time += stoi(tasks[num_of_task][0]);
               empty_time[num_of_empty_time][0] = to_string(updated_time);
            }
        }
        
    }
}

void show_arranged_tasks(vector< vector<string> > &arranged_tasks) {
    vector< vector<int> > new_arranged_tasks;
    vector<int> new_arranged_tasks_1st_d;
    for(int num_of_task = 0; num_of_task < arranged_tasks.size(); num_of_task++) {
       new_arranged_tasks_1st_d.push_back(stoi(arranged_tasks[num_of_task][0]));
       new_arranged_tasks_1st_d.push_back(stoi(arranged_tasks[num_of_task][1]));
       new_arranged_tasks.push_back(new_arranged_tasks_1st_d);
       new_arranged_tasks_1st_d.clear();
       int start_task_hour = (new_arranged_tasks[num_of_task][0]/minutes_per_hour) + beginning_of_day;
       int start_task_minute = new_arranged_tasks[num_of_task][0]%minutes_per_hour;
       int end_task_hour = (new_arranged_tasks[num_of_task][1]/minutes_per_hour) + beginning_of_day;
       int end_task_minute = new_arranged_tasks[num_of_task][1]%minutes_per_hour;
       cout << num_of_task+1 << ' ' << start_task_hour << ':' << setfill('0') <<
       setw(2) << start_task_minute << '-' << end_task_hour << ':' <<setfill('0') <<
       setw(2) << end_task_minute << endl;
    }
}

int main() {
    vector< vector<string> > event_time;
    vector< vector<string> > tasks;
    vector< vector<string> > event_time_in_minute;
    vector< vector<string> > empty_time;
    vector< vector<string> > arranged_tasks;
    scan_event_times(event_time);
    scan_tasks(tasks);
    hour_to_minute(event_time, tasks, event_time_in_minute);
    arrange_empty_times(event_time_in_minute, empty_time);
    put_tasks_in_empty_times(tasks, empty_time, arranged_tasks);
    show_arranged_tasks(arranged_tasks);
    return 0;
}