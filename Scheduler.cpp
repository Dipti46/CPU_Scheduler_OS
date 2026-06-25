//Algorithms actual logic (FCFS, SJF, etc.)
// Turnaround Time (TAT) = Completion Time - Arrival Time
// Waiting Time (WT) = Turnaround Time - Burst Time

#include "Scheduler.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std; 

// comparator to sort on the basis of arrival time
bool compareArrival(const Process& a, const Process& b) {
    return a.arrival_time < b.arrival_time;
}

// to sort on the basis of PID at the end of SJF
bool comparePID(const Process& a, const Process& b) {
    return a.pid < b.pid;
}

void Scheduler::runFCFS(vector<Process>& processes) {
    // 1. sorts the processes based on their arrival time
    sort(processes.begin(), processes.end(), compareArrival);
    
    int current_time = 0;
    cout << "\n--- [Gantt Chart] ---\n|";

    for (size_t i = 0; i < processes.size(); ++i) {
        // if the CPU is idle and no new process has arrived yet
        if (current_time < processes[i].arrival_time) {
            cout << " IDLE (" << processes[i].arrival_time - current_time << "s) |";
            current_time = processes[i].arrival_time;
        }
        
        cout << " P" << processes[i].pid << " (" << processes[i].burst_time << "s) |";
        
        current_time += processes[i].burst_time;
        processes[i].completion_time = current_time;
        
        // Formulas calculation
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
    cout << "\n";
}

void Scheduler::printTable(const vector<Process>& processes) {
    cout << "\n" << string(65, '-') << "\n";
    cout << left << setw(7) << "PID" 
         << setw(10) << "Arrival" 
         << setw(10) << "Burst" 
         << setw(12) << "Completion" 
         << setw(10) << "TAT" 
         << setw(10) << "WT" << "\n";
    cout << string(65, '-') << "\n";

    float total_wt = 0, total_tat = 0;
    
    for (size_t i = 0; i < processes.size(); ++i) {
        cout << left << setw(7) << processes[i].pid 
             << setw(10) << processes[i].arrival_time 
             << setw(10) << processes[i].burst_time 
             << setw(12) << processes[i].completion_time 
             << setw(10) << processes[i].turnaround_time 
             << setw(10) << processes[i].waiting_time << "\n";
             
        total_wt += processes[i].waiting_time;
        total_tat += processes[i].turnaround_time;
    }
    
    cout << string(65, '-') << "\n";
    cout << "Average Waiting Time: " << (total_wt / processes.size()) << "s\n";
    cout << "Average Turnaround Time: " << (total_tat / processes.size()) << "s\n";
}

// Comparator for the priority queue (min-heap): the smaller the burst time, the higher the priority
struct CompareBurst {
    bool operator()(const Process& a, const Process& b) {
        if (a.burst_time == b.burst_time)
            return a.arrival_time > b.arrival_time; // If two processes have the same burst time, the one that arrived earlier is executed first
        return a.burst_time > b.burst_time;
    }
};

void Scheduler::runSJF(vector<Process>& processes) {
    // First sort the processes on the basis of arrival time, same as  FCFS
    sort(processes.begin(), processes.end(), compareArrival);

    vector<Process> completed_processes;
    // Using a Min-Heap with a custom comparator
    priority_queue<Process, vector<Process>, CompareBurst> ready_pq;

    int current_time = 0;
    size_t index = 0;
    int n = processes.size();

    cout << "\n--- [SJF Gantt Chart] ---\n|";

    while (index < n || !ready_pq.empty()) {
        // 1. Push all processes whose arrival time is less than or equal to the current time into the min-heap
        while (index < n && processes[index].arrival_time <= current_time) {
            ready_pq.push(processes[index]);
            index++;
        }

        // 2. If the queue is empty, it indicates that no process has arrived yet, so the CPU remains idle
        if (ready_pq.empty()) {
            cout << " IDLE (" << processes[index].arrival_time - current_time << "s) |";
            current_time = processes[index].arrival_time;
            continue;
        }

        // 3. Pop the process with the minimum burst time from the min-heap
        Process current_process = ready_pq.top();
        ready_pq.pop();

        cout << " P" << current_process.pid << " (" << current_process.burst_time << "s) |";

        // Execution logic
        current_time += current_process.burst_time;
        current_process.completion_time = current_time;
        current_process.turnaround_time = current_process.completion_time - current_process.arrival_time;
        current_process.waiting_time = current_process.turnaround_time - current_process.burst_time;

        completed_processes.push_back(current_process);
    }
    cout << "\n";

    // Updating the original vector with the newly calculated data
    processes = completed_processes;
    
    // Sorting the processes again according to PID so that the table appears clean and organized
    sort(processes.begin(), processes.end(), comparePID);
}