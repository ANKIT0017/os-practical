#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Function to implement First-Fit memory allocation
void firstFit(int blockSize[], int m, int processSize[], int n)
{
    vector<int> allocation(n, -1); // -1 indicates that no block is allocated

    // Iterate over each process
    for (int i = 0; i < n; i++)
    {
        // Find the first block that can accommodate the process
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                allocation[i] = j;
                blockSize[j] -= processSize[i]; // Decrease the block size
                break;
            }
        }
    }

    // Output the result of First-Fit
    cout << "\nFirst-Fit Allocation:" << endl;
    for (int i = 0; i < n; i++)
    {
        if (allocation[i] != -1)
            cout << "Process " << i + 1 << " allocated to Block " << allocation[i] + 1 << endl;
        else
            cout << "Process " << i + 1 << " not allocated" << endl;
    }
}

// Function to implement Best-Fit memory allocation
void bestFit(int blockSize[], int m, int processSize[], int n)
{
    vector<int> allocation(n, -1);

    // Iterate over each process
    for (int i = 0; i < n; i++)
    {
        int bestIdx = -1;
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (bestIdx == -1 || blockSize[bestIdx] > blockSize[j])
                {
                    bestIdx = j;
                }
            }
        }
        // If a block is found, allocate it
        if (bestIdx != -1)
        {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i]; // Decrease the block size
        }
    }

    // Output the result of Best-Fit
    cout << "\nBest-Fit Allocation:" << endl;
    for (int i = 0; i < n; i++)
    {
        if (allocation[i] != -1)
            cout << "Process " << i + 1 << " allocated to Block " << allocation[i] + 1 << endl;
        else
            cout << "Process " << i + 1 << " not allocated" << endl;
    }
}

// Function to implement Worst-Fit memory allocation
void worstFit(int blockSize[], int m, int processSize[], int n)
{
    vector<int> allocation(n, -1);

    // Iterate over each process
    for (int i = 0; i < n; i++)
    {
        int worstIdx = -1;
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (worstIdx == -1 || blockSize[worstIdx] < blockSize[j])
                {
                    worstIdx = j;
                }
            }
        }
        // If a block is found, allocate it
        if (worstIdx != -1)
        {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i]; // Decrease the block size
        }
    }

    // Output the result of Worst-Fit
    cout << "\nWorst-Fit Allocation:" << endl;
    for (int i = 0; i < n; i++)
    {
        if (allocation[i] != -1)
            cout << "Process " << i + 1 << " allocated to Block " << allocation[i] + 1 << endl;
        else
            cout << "Process " << i + 1 << " not allocated" << endl;
    }
}

int main()
{
    int m, n;

    // Input the number of blocks and processes
    cout << "Enter the number of blocks: ";
    cin >> m;
    int blockSize[m];
    cout << "Enter the sizes of the blocks:\n";
    for (int i = 0; i < m; i++)
    {
        cin >> blockSize[i];
    }

    cout << "Enter the number of processes: ";
    cin >> n;
    int processSize[n];
    cout << "Enter the sizes of the processes:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> processSize[i];
    }

    // Create copies of the block sizes for each allocation strategy
    int blockSize1[m], blockSize2[m], blockSize3[m];
    for (int i = 0; i < m; i++)
    {
        blockSize1[i] = blockSize[i];
        blockSize2[i] = blockSize[i];
        blockSize3[i] = blockSize[i];
    }

    // Call functions to implement the three allocation strategies
    firstFit(blockSize1, m, processSize, n);
    bestFit(blockSize2, m, processSize, n);
    worstFit(blockSize3, m, processSize, n);

    return 0;
}
