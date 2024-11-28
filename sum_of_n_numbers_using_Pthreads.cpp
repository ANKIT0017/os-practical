#include <iostream>
#include <pthread.h>

using namespace std;

// Define the number of elements in the array
#define MAX 100

// Structure to pass data to threads
struct ThreadData
{
    int *arr;  // Pointer to the array
    int start; // Starting index for the sublist
    int end;   // Ending index for the sublist
    int sum;   // To store the sum of the sublist
};

// Function that will be executed by each thread to compute the sum of a sublist
void *calculateSum(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    data->sum = 0;

    // Compute the sum of the sublist
    for (int i = data->start; i < data->end; i++)
    {
        data->sum += data->arr[i];
    }

    // Return the sum to the calling thread
    pthread_exit(NULL);
}

int main()
{
    int n;
    cout << "Enter the number of elements in the list (n): ";
    cin >> n;

    int arr[MAX];
    cout << "Enter " << n << " numbers:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    // Create two threads and data for each thread
    pthread_t thread1, thread2;
    ThreadData data1, data2;

    // Define the split of the array into two sublists
    data1.arr = arr;
    data1.start = 0;
    data1.end = n / 2;

    data2.arr = arr;
    data2.start = n / 2;
    data2.end = n;

    // Create the threads to calculate the sum of the sublists
    pthread_create(&thread1, NULL, calculateSum, (void *)&data1);
    pthread_create(&thread2, NULL, calculateSum, (void *)&data2);

    // Wait for the threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Combine the results from both threads
    int totalSum = data1.sum + data2.sum;

    // Output the final sum
    cout << "The sum of the " << n << " numbers is: " << totalSum << endl;

    return 0;
}
