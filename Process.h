// Process ki blueprint (Structure/Class)

#ifndef PROCESS_H
#define PROCESS_H

struct Process {
    int pid;            
    int arrival_time;   
    int burst_time;      
    int remaining_time;  
    int priority;        // for priority sheduling
    
    int completion_time = 0;
    int turnaround_time = 0;
    int waiting_time = 0;
};

#endif