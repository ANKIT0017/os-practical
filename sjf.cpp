#include <iostream>
#include <algorithm> // For using sort

using namespace std;

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

bool compareArrival(Process a, Process b)
{
    return a.arrivalTime < b.arrivalTime;
}

bool compareBurst(Process a, Process b)
{
    return a.burstTime < b.burstTime;
}

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    Process processes[n];

    // Input process details (PID, Arrival Time, Burst Time)
    for (int i = 0; i < n; i++)
    {
        processes[i].pid = i + 1; // Assign PID
        cout << "Enter arrival time and burst time for Process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
    }

    // Sort processes by arrival time (to handle them in the order they arrive)
    sort(processes, processes + n, compareArrival);

    // Completion Time calculation using SJF (non-preemptive)
    int time = 0;                  // Keeps track of current time
    bool isCompleted[n] = {false}; // To keep track of whether a process has been completed

    // Execute processes in the order of shortest burst time
    for (int i = 0; i < n; i++)
    {
        // Find the process with the shortest burst time that has arrived
        int idx = -1;
        int minBurstTime = 1e9; // Arbitrarily large number

        for (int j = 0; j < n; j++)
        {
            if (!isCompleted[j] && processes[j].arrivalTime <= time && processes[j].burstTime < minBurstTime)
            {
                minBurstTime = processes[j].burstTime;
                idx = j;
            }
        }

        // Execute the selected process
        processes[idx].completionTime = time + processes[idx].burstTime;
        processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
        processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;

        // Mark this process as completed
        isCompleted[idx] = true;

        // Update current time
        time = processes[idx].completionTime;
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
