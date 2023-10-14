/* Mayuresh Chavan
 * AI A B2:5 Operating Systems
 * main.cpp
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
#include <ctype.h>
#include <utility>
#include "PCB.cpp"
#include "queue.cpp"
#include "scheduler.cpp"
#include "MemoryManagement.cpp"

using namespace std;

bool is_int(string word) {
    bool is_number = true;
    for(string::const_iterator k = word.begin(); k != word.end(); ++k)
        is_number &= isdigit(*k);
    return is_number;
}

int current_PID = 0;
int PID() {
    current_PID += 1;
    return current_PID;
}

// Prompt user for process information
PCB enter_process_info(string state="0") {
  // PHASE 1
    // string priority, job_time, program_counter, hln = "a";
    // int pid = PID();
    // while (true) {
    //     cout << "Priority (integer): ";
    //     cin >> priority;
    //     if (is_int(priority))
    //         break;
    // }
    // if (state == "0") {
    //     while (state != "ready" && state != "waiting" && state != "running" && state != "terminated") {
    //         cout << "State (ready, waiting): ";//", running, terminated): ";
    //         cin >> state;
    //     }
    // }
    // cout << "Program Counter Address: ";
    // cin >> program_counter;
    // while (true) {
    //     cout << "Job Time (integer): ";
    //     cin >> job_time;
    //     if (is_int(job_time))
    //         break;
    // }
    // while (true) {
    //     cout << "How Long Needed (integer): ";
    //     cin >> hln;
    //     if (is_int(hln))
    //         break;
    // }
    // PCB pcb(pid, stoi(priority), state, program_counter, stoi(job_time), stoi(hln));
    // return pcb;
  // PHASE 2
    string pid, arrival_time, duration, mem_size;
    cout << "PID: ";
    cin >> pid;
    cout << "Arrival Time: ";
    cin >> arrival_time;
    cout << "Duration: ";
    cin >> duration;
    cout << "Memory Size: ";
    cin >> mem_size;
    PCB pcb(stoi(pid), stoi(arrival_time), stoi(duration), stoi(mem_size));
    return pcb;
}

// The main worked method of the operating system
int main() {
    cout << "\n===========================================================\n";
    cout << "|           AI A B2:5 : Operating Systems Project           |\n";
    cout << "|                                                           |\n";
    cout << "===========================================================\n";
    int mode = -1;
    while (mode != 1 && mode != 2 && mode != 0) {
        cout << "\nPlease select an option:\n";
        cout << "   1  -  Manually Enter Processes.\n";
        cout << "   2  -  Read Processes in from text file.\n";
        cout << "   0  -  Exit Operating System.\n> ";
        cin >> mode;
    }
    vector<PCB> ready;
    vector<PCB> waiting;
    vector<PCB> running;
    vector<PCB> terminated;
    MemoryManagement mm, mm1, mm2;

    if (mode == 1) { // Manually Enter Processes
        cout << "\nManual Mode selected. Please enter in the process information:\n";

        char entering_processes = 'y';
        while (entering_processes == 'y') {
            PCB pcb = enter_process_info();
            // move PCB into correct queue
          // PHASE 1
            // if (pcb.get_state() == "ready") {
            //     ready.push_back(pcb);
            // } else if (pcb.get_state() == "waiting") {
            //     waiting.push_back(pcb);
            // } else if (pcb.get_state() == "running") {
            //     running.push_back(pcb);
            // } else if (pcb.get_state() == "terminated") {
            //     terminated.push_back(pcb);
            // }
          // PHASE 2
            ready.push_back(pcb);
            // prompt user for another process to input
            cout << "\nEnter another process? (y/n): ";
            cin >> entering_processes;
            cout << endl;
        }
    } else if (mode == 2) { // Read processes from text file
        cout << "\nPlease enter the name of .txt file to read processes from: ";
        string file_name;
        cin >> file_name;
        // string file_name = "input.txt";
        // cout << endl;

        fstream file;
        file.open(file_name);
        if (file.is_open()){
            // PHASE 1
            // string line;
            // while (getline(file, line)) {
            //     // if (line.at(0) == '#') { // ignore comments
            //     //     continue;
            //     // }
            //
            //     stringstream ss(line);
            //     string priority, job_time, state, program_counter, hln;
            //     int pid = PID();
            //     ss >> priority;
            //     ss >> state;
            //     ss >> program_counter;
            //     if (ss >> job_time)
            //         cout << "";
            //     else
            //         job_time = "0";
            //     ss >> hln;
            //     // remove possible comments from inputs
            //     regex regex(",");
            //     priority = regex_replace(priority, regex, "");
            //     job_time = regex_replace(job_time, regex, "");
            //     state = regex_replace(state, regex, "");
            //     program_counter = regex_replace(program_counter, regex, "");
            //     hln = regex_replace(hln, regex, "");
            //     PCB pcb(pid, stoi(priority), state, program_counter, stoi(job_time), stoi(hln));
            //     // move PCB into correct queue
            //     if (pcb.get_state() == "ready") {
            //         ready.push_back(pcb);
            //     } else if (pcb.get_state() == "waiting") {
            //         waiting.push_back(pcb);
            //     } else if (pcb.get_state() == "running") {
            //         running.push_back(pcb);
            //     } else if (pcb.get_state() == "terminated") {
            //         terminated.push_back(pcb);
            //     }
            // }

            // PHASE 2
            string line;
            getline(file, line);
            int size_of_memory = stoi(line);
            getline(file, line);
            int number_of_available_spaces = stoi(line);
            vector<int> starting_address;
            vector<int> available_space;
            string temp;
            for (int i=0; i<number_of_available_spaces; i++) {
                getline(file, line);
                stringstream ss(line);
                ss >> temp;
                starting_address.push_back(stoi(temp));
                ss >> temp;
                available_space.push_back(stoi(temp));
            }
            getline(file, line);
            int number_processes = stoi(line);
            for (int i=0; i<number_processes; i++) {
                getline(file, line);
                stringstream ss(line);
                string pid, arrival_time, duration, p_mem_size;
                ss >> pid;
                ss >> arrival_time;
                ss >> duration;
                ss >> p_mem_size;
                ready.push_back(PCB(stoi(pid), stoi(arrival_time), stoi(duration), stoi(p_mem_size)));
            }
            mm = MemoryManagement(size_of_memory, starting_address, available_space, number_processes, ready);
            mm1 = MemoryManagement(size_of_memory, starting_address, available_space, number_processes, ready);
            mm2 = MemoryManagement(size_of_memory, starting_address, available_space, number_processes, ready);
        } else {
            cerr << "Error opening " << file_name << endl;
            exit(1);
        }
    } else if (mode == 0) {
        cout << "\nQuitting Operating System. Have a good day.\n\n";
        return 0;
    }

    // create queues based on processes
    Queue ready_queue("Ready", ready);
    Queue waiting_queue("Waiting", waiting);
    // Queue running_queue("Running", running);
    // Queue terminated_queue("terminated", terminated);

    bool using_os = true;
    while (using_os) {
        cout << "\nPlease select an option:\n";
        cout << "   1  -  Print contents of Ready Queue.\n";
        cout << "   2  -  Print contents of Waiting Queue.\n";
        // cout << "   3  -  Print contents of Running Queue.\n";
        // cout << "   4  -  Print contents of Terminated Queue.\n";
        cout << "   3  -  Run the Shortest Job First Scheduler on the Ready queue.\n";
        cout << "   4  -  Run the Priority Scheduler on the Ready queue.\n";
        cout << "   5  -  Run the Round Robin Scheduler on the Ready queue.\n";
        cout << "   6  -  Run all of the schedulers on the Ready queue.\n";
        cout << "   7  -  Add PCB to a given queue.\n";
        cout << "   8  -  Delete PCB from given queue.\n";
        cout << "   9  -  Phase 2: Run First Fit, Best Fit, and Worst Fit algorithms.\n";
        cout << "   0  -  Exit Operating System.\n";

        int input;
        cout << "> ";
        cin >> input;
        cout << endl;
        int q;
        string queue_selected;
        PCB pcb;
        double result, result1, result2;
        switch(input) {
            case 1 :    ready_queue.print();
                        break;
            case 2 :    waiting_queue.print();
                        break;
            case 3 :    cout << "\nRunning the Shortest Job First Scheduler.\n";
                        result = sjf_scheduler(ready_queue,waiting_queue);
                        cout << "\nShortest Job First Scheduler average wait time: " << result << endl;
                        break;
            case 4 :    cout << "\nRunning the Priority Scheduler.\n";
                        result = priority_scheduler(ready_queue, waiting_queue);
                        cout << "\nPriority Scheduler average wait time: " << result << endl;
                        break;
            case 5 :    cout << "Please enter the Time Quantum to use: ";
                        cin >> q;
                        cout << "\nRunning the Round Robin Scheduler.\n";
                        result = rr_scheduler(ready_queue, waiting_queue, q);
                        cout << "\nRound Robin Scheduler (q = " << q << ") average wait time: " << result << endl;
                        break;
            case 6 :    cout << "Please enter the Time Quantum to use: ";
                        cin >> q;
                        cout << "\nRunning the Shortest Job First Scheduler.\n";
                        result = sjf_scheduler(ready_queue,waiting_queue);
                        cout << "\nRunning the Priority Scheduler.\n";
                        result1 = priority_scheduler(ready_queue, waiting_queue);
                        cout << "\nRunning the Round Robin Scheduler.\n";
                        result2 = rr_scheduler(ready_queue, waiting_queue, q);
                        cout << "\n\nResults:\nShortest Job First Scheduler average wait time:    " << result << endl;
                        cout << "Priority Scheduler average wait time:              " << result1 << endl;
                        cout << "Round Robin Scheduler (q = " << q << ") average wait time:   " << result2 << endl;
                        break;
            case 7 :    cout << "Add PCB to which queue? (ready, waiting): ";
                        cin >> queue_selected;
                        if (queue_selected == "ready") {
                            pcb = enter_process_info("ready");
                            ready_queue.push(pcb,ready_queue.length()+1);
                            break;
                        } else if (queue_selected == "waiting") {
                            pcb = enter_process_info("waiting");
                            waiting_queue.push(pcb,waiting_queue.length()+1);
                            break;
                        } else {
                            cout << "Invalid queue name\n";
                            break;
                        }
                        break;
            case 8 :    cout << "Delete PCB from which queue? (ready, waiting): ";
                        cin >> queue_selected;
                        if (queue_selected == "ready") {
                            ready_queue.print();
                            cout << "\nPlease enter the PID of the PCB you wish to delete: ";
                            cin >> q;
                            ready_queue.delete_PCB(q);
                            break;
                        } else if (queue_selected == "waiting") {
                            waiting_queue.print();
                            cout << "\nPlease enter the PID of the PCB you wish to delete: ";
                            cin >> q;
                            waiting_queue.delete_PCB(q);
                            break;
                        } else {
                            cout << "Invaild queue name.\n";
                            break;
                        }
                        break;
            case 9 :    cout << "Phase 2 of OS Project\n";
                        mm.FirstFit();
                        cout << endl;
                        mm1.BestFit();
                        cout << endl;
                        mm2.WorstFit();
                        cout << endl;
                        break;
            case 0 :    cout << "Quitting Operating System. Have a good day.\n";
                        using_os = false;
                        break;
            default :   cout << "Please enter in a valid command.\n\n";
                        break;
        }
    }

    return 0;
}
