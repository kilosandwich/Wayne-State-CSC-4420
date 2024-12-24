// CPP Program to implement merge sort using
// multi-threading
#include <iostream>
#include <pthread.h>
#include <time.h>
 
using namespace std;

//this value can be fixed still. I wish it were an input, but whatever
//this value needs to be 10,000,00 (that's 6 zeroes) or 1000000
#define MAX 1000000
 
// array of size MAX
int a[MAX];
int part = 0;

//our mutex for locking and unlocking while merging to avoid race conditions
pthread_mutex_t mutex; 
// merge function for merging two parts
void merge(int low, int mid, int high)
{
    int* left = new int[mid - low + 1];
    int* right = new int[high - mid];
 
    // n1 is size of left part and n2 is size
    // of right part
    int n1 = mid - low + 1, n2 = high - mid, i, j;
 
    // storing values in left part
    for (i = 0; i < n1; i++)
        left[i] = a[i + low];
 
    // storing values in right part
    for (i = 0; i < n2; i++)
        right[i] = a[i + mid + 1];
 
    int k = low;
    i = j = 0;
 
    // merge left and right in ascending order
    while (i < n1 && j < n2) {
        if (left[i] <= right[j])
            a[k++] = left[i++];
        else
            a[k++] = right[j++];
    }
 
    // insert remaining values from left
    while (i < n1) {
        a[k++] = left[i++];
    }
 
    // insert remaining values from right
    while (j < n2) {
        a[k++] = right[j++];
    }
    delete[] left;
    delete[] right;
}
 
// merge sort function
void merge_sort(int low, int high)
{
    // calculating mid point of array
    int mid = low + (high - low) / 2;
    if (low < high) {
 
        // calling first half
        merge_sort(low, mid);
 
        // calling second half
        merge_sort(mid + 1, high);
 
        // merging the two halves
        merge(low, mid, high);
    }
}

// Thread function for multi-threading
//This is a new function for performing merge sort for the threads themselves
void* thread_merge_sort(void* arg) {
    pthread_mutex_lock(&mutex); //we are accessing the shared variable
    //NO ONE ELSE CAN HAVE IT
    int thread_part = part++;
    //We have accesssed the shared variable, we are done, unlcok the mutex
    pthread_mutex_unlock(&mutex);

    // Calculating low and high
    int low = thread_part * (MAX / *(int*)arg);
    int high = (thread_part + 1) * (MAX / *(int*)arg) - 1;

    // Evaluating mid point
    int mid = low + (high - low) / 2;
    if (low < high) {
        merge_sort(low, mid);
        merge_sort(mid + 1, high);
        merge(low, mid, high);
    }
    return NULL;
}

 
// thread function for multi-threading
void* merge_sort(void* arg)
{
    // which part out of 4 parts
    int thread_part = part++;
 
    // calculating low and high
    int low = thread_part * (MAX / 4);
    int high = (thread_part + 1) * (MAX / 4) - 1;
 
    // evaluating mid point
    int mid = low + (high - low) / 2;
    if (low < high) {
        merge_sort(low, mid);
        merge_sort(mid + 1, high);
        merge(low, mid, high);
    }
}
 
// Driver Code
//converted the original maine function into a separate generalized function
//purely because I don't want to upload multiple c++
void sortALot(int THREAD_MAX)
{
    // generating random values in array
    for (int i = 0; i < MAX; i++)
        a[i] = rand() % 100;
 
    // t1 and t2 for calculating time for
    // merge sort
    clock_t t1, t2;
 
    t1 = clock();
    pthread_t threads[THREAD_MAX];
 
    // creating ANY number of threads not just 4 
    for (int i = 0; i < THREAD_MAX; i++)
        pthread_create(&threads[i], NULL, thread_merge_sort, &THREAD_MAX);
 
    // joining all 4 threads
    //This section of code had to be altered, the join was hardcoded for 4.
    for (int i = 0; i < THREAD_MAX; i++)
        pthread_join(threads[i], NULL);
 
    // merging the final 4 parts
    //MERGE EVERYTHING NOT JUST 4
    //It's really confusing to me that everything is in one array
    //but whatever. 
    for (int size = MAX / THREAD_MAX; size < MAX; size *= 2) {
        for (int low = 0; low < MAX - size; low += 2 * size) {
            int mid = low + size - 1;
            int high = min(low + 2 * size - 1, MAX - 1);
            merge(low, mid, high);
        }
    }
    t2 = clock();
 
    // displaying sorted array
    cout << "Sorted array: ";
    for (int i = 0; i < MAX; i++)
       cout << a[i] << " ";
    cout << endl << "Threads used: " << THREAD_MAX << endl;
    // time taken by merge sort in seconds
    cout << "Time taken: " << (t2 - t1) / 
              (double)CLOCKS_PER_SEC << endl;
    return;
}




int main(int argc, char* argv[]){
    int n;
    cout << endl << "Please input the number of threads you wish to use: "<< endl;
    cin >> n;
    cout << endl;
    
    sortALot(n);
    return 0;
    
}
