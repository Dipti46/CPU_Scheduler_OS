//Scheduling algorithms ki declarations

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include "Process.h"

class Scheduler {
public:
    // First Come First Served Algorithm
    static void runFCFS(std::vector<Process>& processes);

    static void runSJF(std::vector<Process>& processes);
    
    // to print the result in terminal
    static void printTable(const std::vector<Process>& processes);
};

#endif