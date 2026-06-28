# CPU Scheduling Simulator (C++)

A performance-focused command-line interface (CLI) simulator that implements Operating System CPU scheduling algorithms. Built using **Modern C++**, this tool helps visualize how processes are scheduled in an OS.

## 🚀 Features Implemented
- **First Come First Served (FCFS):** Non-preemptive scheduling based on arrival times.
- **Shortest Job First (SJF):** Non-preemptive scheduling that dynamically selects the shortest job using a Min-Heap (`std::priority_queue`).
- **Round Robin (RR):** Preemptive scheduling that allocates CPU time slices based on a dynamic *Time Quantum*, strictly adhering to standard OS queuing criteria (interleaved execution context).
- **Priority Scheduling:** Non-preemptive priority-based allocation using a Min-Heap (`std::priority_queue`), equipped with an automatic arrival-time tie-breaker mechanism.
- **Gantt Chart Visualization:** Live rendering of execution timelines, including CPU **IDLE** states.
- **Pro Formatting:** Tabular output rendered beautifully using optimized C-style `printf` spacing.

## 📂 Project Structure
- `Process.h`: Contains the core process blueprint (`struct`).
- `Scheduler.h`: Declaration of the `Scheduler` engine class.
- `Scheduler.cpp`: Core implementation of FCFS, SJF, RR, Priority Scheduling and table rendering.
- `main.cpp`: Interactive menu-driven entry point.
- `.gitignore`: Configured to block machine-generated binaries (`.exe`).

## 💻 How to Run
Compile and execute the simulator using `g++`:
```bash
g++ main.cpp Scheduler.cpp -o scheduler.exe ; .\scheduler.exe