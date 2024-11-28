#include <iostream>
#include <climits> // For INT_MAX

using namespace std;

struct Process
{
    int pid;            // Process ID
    int arrivalTime;    // Arrival Time
    int burstTime;      // Burst Time
    int remainingTime;  // Remaining Time
    int completionTime; // Completion Time
    int turnaroundTime; // Turnaround Time
    int waitingTime;    // Waiting Time
};

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    // Array to store the processes
    Process processes[n];

    // Input process details (PID, Arrival Time, Burst Time)
    for (int i = 0; i < n; i++)
    {
        processes[i].pid = i + 1; // Assign PID
        cout << "Enter arrival time and burst time for Process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime; // Initialize remaining time with burst time
    }

    // Sort processes by arrival time (using a simple sorting algorithm)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (processes[i].arrivalTime > processes[j].arrivalTime)
            {
                // Swap the processes[i] and processes[j]
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    // Variables for time and completion tracking
    int time = 0; // Keeps track of current time
    int completed = 0;
    int lastProcessIndex = -1;

    bool isCompleted[n] = {false}; // To keep track of completed processes

    // Run the process using SRTF (Shortest Remaining Time First)
    while (completed < n)
    {
        int idx = -1;
        int minRemainingTime = INT_MAX; // Arbitrarily large number

        // Find the process with the shortest remaining time that has arrived
        for (int i = 0; i < n; i++)
        {
            if (!isCompleted[i] && processes[i].arrivalTime <= time && processes[i].remainingTime < minRemainingTime)
            {
                minRemainingTime = processes[i].remainingTime;
                idx = i;
            }
        }

        if (idx != -1)
        {
            // Run the process for one time unit
            processes[idx].remainingTime--;
            time++; // Update current time

            // If the process has finished, calculate the times and mark it as completed
            if (processes[idx].remainingTime == 0)
            {
                processes[idx].completionTime = time;
                processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
                isCompleted[idx] = true;
                completed++;
            }
        }
        else
        {
            // If no process is ready, increment time
            time++;
        }
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
