#include <iostream>

using namespace std;

// Define maximum number of processes
#define MAX_PROCESSES 100

// Structure to store process information
struct Process
{
    int pid;            // Process ID
    int arrivalTime;    // Arrival Time
    int burstTime;      // Burst Time (execution time)
    int completionTime; // Completion Time
    int turnaroundTime; // Turnaround Time
    int waitingTime;    // Waiting Time
};

int main()
{
    int n;
    Process processes[MAX_PROCESSES];

    // Input number of processes
    cout << "Enter number of processes: ";
    cin >> n;

    // Input process details (PID, Arrival Time, Burst Time)
    for (int i = 0; i < n; i++)
    {
        processes[i].pid = i + 1; // Assign PID
        cout << "Enter arrival time and burst time for Process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
    }

    // Sort processes based on arrival time manually (Bubble Sort)
    // This is done without using `sort()` or any algorithm library
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime)
            {
                // Swap the processes if they are in the wrong order
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Completion time for the first process is its arrival time + burst time
    processes[0].completionTime = processes[0].arrivalTime + processes[0].burstTime;

    // Calculate completion time, turnaround time, and waiting time for each process
    for (int i = 1; i < n; i++)
    {
        processes[i].completionTime = max(processes[i].arrivalTime, processes[i - 1].completionTime) + processes[i].burstTime;
    }

    // Calculate turnaround time and waiting time for each process
    for (int i = 0; i < n; i++)
    {
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
    }

    // Display the process information
    cout << "PID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++)
    {
        cout << processes[i].pid << "\t"
             << processes[i].arrivalTime << "\t\t"
             << processes[i].burstTime << "\t\t"
             << processes[i].completionTime << "\t\t"
             << processes[i].turnaroundTime << "\t\t"
             << processes[i].waitingTime << endl;
    }

    return 0;
}
