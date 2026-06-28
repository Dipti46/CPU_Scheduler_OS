// Main execution loop

#include <iostream>
#include <vector>
#include "Process.h"
#include "Scheduler.h"

using namespace std;

int main() {
    int num_processes, choice;
    
    cout << "=== OS CPU Scheduler Simulator ===\n";
    cout << "Enter the number of processes: ";
    cin >> num_processes;

    vector<Process> processes(num_processes);

    // getting data from the user during runtime
    for (int i = 0; i < num_processes; ++i) {
        processes[i].pid = i + 1;
        cout << "\nFor Process P" << processes[i].pid << ":\n";
        cout << "  Enter Arrival Time: ";
        cin >> processes[i].arrival_time;
        cout << "  Enter Burst Time: ";
        cin >> processes[i].burst_time;
        cout << "  Enter Priority (Lower number = Higher Priority): ";
        cin >> processes[i].priority;
        processes[i].remaining_time = processes[i].burst_time; 
    }

    vector<Process> processes_backup = processes;

    do {
        cout << "\n===============================";
        cout << "\nSelect Scheduling Algorithm:";
        cout << "\n1. First Come First Served (FCFS)";
        cout << "\n2. Shortest Job First (SJF)";
        cout << "\n3. Round Robin (RR)";
        cout << "\n4. Priority Scheduling";
        cout << "\n3. Exit";
        cout << "\nEnter choice (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1: {
                vector<Process> temp = processes_backup;
                cout << "\nRunning FCFS...";
                Scheduler::runFCFS(temp);
                Scheduler::printTable(temp);
                break;
            }
            case 2: {
                vector<Process> temp = processes_backup;
                cout << "\nRunning SJF...";
                Scheduler::runSJF(temp);
                Scheduler::printTable(temp);
                break;
            }
            case 3: {
                vector<Process> temp = processes_backup;
                int tq;
                cout << "Enter Time Quantum for Round Robin: ";
                cin >> tq;
                cout << "\nRunning Round Robin...";
                Scheduler::runRoundRobin(temp, tq);
                Scheduler::printTable(temp);
                break;
            }
            case 4: {
                vector<Process> temp = processes_backup;
                cout << "\nRunning Priority Scheduling...";
                Scheduler::runPriority(temp);
                Scheduler::printTable(temp);
                break;
            }
            case 5:
                cout << "\nExiting Simulator...\n";
                break;
            default:
                cout << "\nInvalid choice! Please try again...";
        }
    } while (choice != 5);

    return 0;
}