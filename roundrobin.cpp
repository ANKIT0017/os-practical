#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

// Structure for a process
struct Process
{
    int pid;            // Process ID
    int arrivalTime;    // Arrival time of the process
    int burstTime;      // Burst time (time required for execution)
    int remainingTime;  // Remaining burst time (for round robin)
    int startTime;      // Start time of the process
    int finishTime;     // Finish time of the process
    int waitingTime;    // Waiting time for the process
    int turnaroundTime; // Turnaround time for the process
};

// Function to implement Round Robin Scheduling with time quantum = 2
void roundRobinScheduling(vector<Process> &processes, int timeQuantum)
{
    queue<Process *> readyQueue;
    vector<int> completionTime(processes.size(), 0);
    int currentTime = 0;

    // Initialize the ready queue with the processes
    for (auto &process : processes)
    {
        process.remainingTime = process.burstTime;
        readyQueue.push(&process);
    }

    // Process scheduling loop
    while (!readyQueue.empty())
    {
        Process *currentProcess = readyQueue.front();
        readyQueue.pop();

        // If the process requires more time than the time quantum, add it back to the queue with updated remaining time
        int executionTime = min(currentProcess->remainingTime, timeQuantum);
        currentProcess->remainingTime -= executionTime;
        currentTime += executionTime;

        // If the process has finished, calculate its final stats
        if (currentProcess->remainingTime == 0)
        {
            currentProcess->finishTime = currentTime;
            currentProcess->turnaroundTime = currentProcess->finishTime - currentProcess->arrivalTime;
            currentProcess->waitingTime = currentProcess->turnaroundTime - currentProcess->burstTime;

            cout << "Process " << currentProcess->pid << " - Start Time: " << currentProcess->startTime
                 << ", Finish Time: " << currentProcess->finishTime
                 << ", Turnaround Time: " << currentProcess->turnaroundTime
                 << ", Waiting Time: " << currentProcess->waitingTime << endl;
        }
        // If the process has not finished, re-add it to the queue
        else
        {
            readyQueue.push(currentProcess);
        }
    }
}

int main()
{
    int n;

    // Input number of processes
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input process details
    for (int i = 0; i < n; i++)
    {
        processes[i].pid = i + 1;
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
    }

    cout << "\nRound Robin Scheduling (Time Quantum = 2):\n";
    roundRobinScheduling(processes, 2);

    return 0;
}
