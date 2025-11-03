// Better Sorts
// 110191019, YU-TING CHUNG
// 2025/04/07

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

int N;       // input size
int R = 500; // number of repetitions
char **data; // input data
char **A;    // array to be sorted
char **B;

void Heapify(char **list, int i, int n);
void HeapSort(char **list, int n);
void Merge(char **list, int low, int mid, int high);
void MergeSort(char **list, int low, int high);
void MergeSort1(char **list, int low, int high);
void InsertionSort(char **list, int low, int high);
void QuickSort(char **list, int low, int high);
void QuickSort1(char **list, int low, int high);
int Partition(char **list, int low, int high);
void Swap(char **list, int i, int j);
void RQuickSort(char **list, int low, int high);
void readInput(void);
double GetTime(void);
void printArray(char **A);
void copyArray(char **data, char **A);

void Heapify(char **list, int i, int n)
{
    int j;    
    int done;
    char *temp;     
    temp = list[i];

    if (i == 0) {
        j = 1;
    }

    else {
        j = 2 * i + 1;  
    }

    done = 0;
    while (j < n && (!done)) {
        
        if (j < n - 1 && strcmp(list[j], list[j + 1]) < 0){  
            
            j = j + 1;  
        }

        if (strcmp(temp, list[j]) > 0) {       // A[i] is already the max
            done = 1;
        }

        else {  
            list[(j - 1) / 2] = list[j];
            j = j * 2 + 1;
        }
    }
    list[(j - 1) / 2] = temp;                 // temp finds right position
}

void HeapSort(char **list, int n)	          // in-place heap sort
{
	int i;							          // index
    char *temp;						          // temporary word

	for (i = (n-1) / 2; i >= 0; i--) {	      // make the list a max heap
		Heapify(list, i, n);
	}

	for (i = n-1 ; i >0; i--) {
        temp = list[i];                                     
		list[i] = list[0];
		list[0] = temp;		                 // move maximum to the end
		Heapify(list, 0, i);	                     
	}
}

void Merge(char **list, int low, int mid, int high) 
{
    int left_idx = low;                     // the index of A[low:mid]
    int right_idx = mid + 1;                // the index of A[mid + 1:high]
    int left_count = 0;
    int right_count = 0; 
    int i = low;                            // B's index
    int k;                                  // loop index
    int n1 = mid - low + 1;
    int n2 =  high - mid;

    while (left_count < n1 && right_count < n2) {

        // add smaller element between right and left part
        if (strcmp(list[left_idx + left_count], 
            list[right_idx + right_count]) < 0) { 
            // current left part is smaller
            B[i] = list[left_idx + left_count]; 
            left_count++;   // update counter
        }

        else {              // current right part is smaller
            B[i] = list[right_idx + right_count];
            right_count++;  // update counter
        }
        i++;                // update B index counter
    }

    while (left_count < n1) {
        B[i] = list[left_idx + left_count];
        left_count++;       // update counter
        i++;                // update B index counter
    }

    while (right_count < n2) {
        B[i] = list[right_idx + right_count];
        right_count++;      // update counter
        i++;                // update B index counter
    }

    // copy B to list
    for (k = low; k <= high; k++) {
        list[k] = B[k];
    }
}

void MergeSort(char **list, int low, int high)  
{
    int mid = (low + high) / 2;         // middle index

    if (low < high) {                   // if at least two elements
        MergeSort(list, low, mid);
        MergeSort(list, mid + 1, high);
        Merge(list, low, mid, high);    // merge left and right part
    }
}

void MergeSort1(char **list, int low, int high)
{
    if ((high - low) < 15) // When A is small, perform insertion sort
    {
        InsertionSort(list, low, high);
        return;
    }

    else
    {   //For large A, divide-and-conquer merge sort
        int mid;
        mid = (low + high) / 2;
        MergeSort1(list, low, mid);      // left part
        MergeSort1(list, mid + 1, high); // right part
        Merge(list, low, mid, high);
    }
}

void InsertionSort(char **list, int low, int high)
{
    int i, j;
    char *temp;

    // Check for every low < j ≤ high
    for (j = low + 1; j <= high; j++)
    {
        temp = list[j]; // Compare A[i] and A[j], i<j
        i = j - 1;
        while (i >= low && strcmp(temp, list[i]) < 0)
        {   // Make room for item = A[j]
            list[i + 1] = list[i];
            i = i - 1;
        }
        list[i + 1] = temp;  // Store item.
    }
}

void QuickSort(char **list, int low, int high)
{
    int mid;
    if (low < high)
    {
        mid = Partition(list, low, high);
        QuickSort(list, low, mid - 1);
        QuickSort(list, mid + 1, high);
    }
}

void QuickSort1(char **list, int low, int high)
{
    int mid;
    if ((high - low) < 15)
    {
        InsertionSort(list, low, high);
        return;
    }
    
    else
    {
        mid = Partition(list, low, high);
        QuickSort1(list, low, mid - 1);
        QuickSort1(list, mid + 1, high);
    }
}

int Partition(char **list, int low, int high) {
    char* v = list[low];
    int i = low + 1;
    int j = high;
    while (1) { // Check for all elements

        // Find i such that A[i] ≥ v
        while (i <= high && strcmp(list[i], v) < 0) i++; 

        // Find j such that A[j] ≤ v
        while (j >= low+1 && strcmp(list[j], v) > 0) j--;
        if (i >= j) break;
        Swap(list, i, j);    // Exchange A[i] and A[j]
        i++;
        j--;
    }
    Swap(list, low, j);  // put pivot to correct position
    return j;
}

void Swap(char **list, int i, int j)
{
    char *t;
    t = list[i];
    list[i] = list[j];
    list[j] = t;
}

void RQuickSort(char **list, int low, int high)
{
    int mid;
    if (low < high)
    {
        if ((high - low) > 5)
        {
            Swap(list, low + (rand() % (high - low + 1)), low);
        }
        mid = Partition(list, low, high);
        RQuickSort(list, low, mid - 1);
        RQuickSort(list, mid + 1, high);
    }
}

void readInput(void)                            // read all inputs
{
    int i;
    char tempWord[1000];                        // store input temporarily

    scanf("%d", &N);                            // input number of entries
    data = (char **)malloc(sizeof(char *) * N); // allocate memory for pointers
    for (i = 0; i < N; i++)
    {
        scanf("%s", tempWord); // input a word
        data[i] = (char *)malloc(sizeof(char) * (strlen(tempWord) + 1));
        strcpy(data[i], tempWord);              // transfer the input to array
    }
}

double GetTime(void)         // get local time in seconds
{
    struct timeval tv;       // variable to store time

    gettimeofday(&tv, NULL); // get local time

    return tv.tv_sec + 1e-6 * tv.tv_usec; // return local time in seconds
}

void printArray(char **A) // print the content of array A
{
    int i; // index

    for (i = 0; i < N; i++)
    {
        printf("%d %s\n", i + 1, A[i]); // print the index and array content
    }
}

void copyArray(char **data, char **A) // copy data to array A
{
    int i; // index

    for (i = 0; i < N; i++)
    {
        A[i] = (char *)malloc(strlen(data[i]) + 1);
        strcpy(A[i],data[i]); // copy content from array data to A
    }
}

int main(void)
{
    int i, high, low;    // loop index
    double t; // for CPU time tracking

    readInput(); // read input to data array
    printf("N = %d\n", N); // print input size

    A = (char**)malloc(sizeof(char*) * N);
    B = (char**)malloc(sizeof(char*) * N);

    copyArray(data, A);
    t = GetTime(); // initialize time counter
    for (i = 0; i < R; i++)
    {
        HeapSort(A, N);
    }
    t = (GetTime() - t) / R;                        // CPU time per iteration
    printf("HeapSort CPU time: %.5e s\n", t);       // print out CPU time

    copyArray(data, A);
    t = GetTime();                                 // initialize time counter
    for (i = 0; i < R; i++)
    {
        MergeSort(A, 0, N-1);
    }
    t = (GetTime() - t) / R;                       // CPU time per iteration
    printf("MergeSort CPU time: %.5e s\n", t);     // print out CPU time

    copyArray(data, A);
    t = GetTime();                                // initialize time counter
    for (i = 0; i < R; i++)
    {
        MergeSort1(A, 0, N-1);
    }
    t = (GetTime() - t) / R;                       // CPU time per iteration
    printf("MergeSort1 CPU time: %.5e s\n", t);    // print out CPU time

    copyArray(data, A);
    t = GetTime();                                // initialize time counter
    for (i = 0; i < R; i++)
    {
        QuickSort(A, 0, N-1);
    }
    t = (GetTime() - t) / R; 
    printf("QuickSort CPU time: %.5e s\n", t);

    copyArray(data, A);
    t = GetTime();                               // initialize time counter
    for (i = 0; i < R; i++)
    {
        QuickSort1(A, 0, N-1);
    }
    t = (GetTime() - t) / R;                    // CPU time per iteration
    printf("QuickSort1 CPU time: %.5e s\n", t);

    copyArray(data, A);
    t = GetTime();                              // initialize time counter
    for (i = 0; i < R; i++)
    {
        RQuickSort(A, 0, N-1);
    }
    t = (GetTime() - t) / R;                    // CPU time per iteration
    printf("RQuickSort CPU time: %.5e s\n", t);
    printArray(A);                              // print sorted array
}
