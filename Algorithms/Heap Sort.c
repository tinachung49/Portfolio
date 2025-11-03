// Heap Sort
// 110191019, YU-TING CHUNG
// 2025/03/17

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

int N;								        // input size
int R = 500;						        // number of repetitions
char **data;						        // input data
char **A;							        // array to be sorted

void Heapify(char **list, int i, int n);	// enforce max heap property
void BUHeapify(char **list, int i, int n);	// enforce max heap property
void Heapify1(char **list, int i, int n);	// enforce max heap property
void BUHeapify1(char **list, int i, int n);	// enforce max heap property
void HeapSort(char **list, int n);          // heap sort with strcmp
void BUHeapSort(char **list, int n);        // buttom-up heap sort with strcmp
void HeapSort1(char **list, int n);         // heap sort with compare
void BUHeapSort1(char **list, int n);       // buttom-up heap sort with compare
void readInput(void);				        // read all inputs
double GetTime(void);					    // get local time in seconds
int compare(char *str1, char *str2);
void copyArray(char **data, char **A);
void printArray(char **A);

void Heapify(char **list, int i, int n)	
{
	int j;								                            // index
	int done;							                            // loop flag
	char *temp;						                                // temporary word

	j = 2 * (i+1)-1;				                                // initialize j to be lchild of i
	temp = list[i];					                                // copy root element
	done = 0;
	while ((j <= n-1) && (!done)) {         
		if ((j< n-1 ) && (strcmp(list[j], list[j + 1]) < 0)) { 
			j++;
		}
		if (strcmp(temp, list[j]) > 0) {
			done = 1;					                            // exit if root is larger
		}
		else {
			list[(j+1) / 2-1] = list[j];                            // replace j's parent with list[j]
			j = 2 * j;		                                        // move j to its lchild
		}
	}
	list[(j+1)/ 2-1] = temp;	                                    // move original root to proper place
}

void BUHeapify(char **list, int i, int n) {
    char *t;
    char *temp;
    int j;
    
    j = i;
    while (2 * (j+1) < n) {                                         // j’s rchild exists
        if (strcmp(list[2 * j + 1], list[2 * j + 2]) > 0) {
            j = 2 * j + 1;                                          // to lchild
        } else {
            j = 2 * j + 2;                                          // to rchild
        }
    }

    if (2 * j+1 <n) {                                               // lchild exits, move to it
        j = 2 * j + 1;
    }

    while (strcmp(list[i], list[j]) > 0) {
        j = (j - 1) / 2;
    }

    temp = list[j];                                                 // store list[j]
    list[j] = list[i];                                              // move A[i] to A[j]

    while (j > i) {                                                 // move all nodes up along the path
        j = (j - 1) / 2;
        t = list[j];
        list[j] = temp;
        temp = t;
    }
}

void Heapify1(char **list, int i, int n)	
{
	int j;								                            // index
	int done;							                            // loop flag
	char *temp;						                                // temporary word

	j = 2 * (i+1)-1;				                                // initialize j to be lchild of i
	temp = list[i];					                                // copy root element
	done = 0;
	while ((j <= n-1) && (!done)) {
		if ((j< n-1 ) && (compare(list[j], list[j + 1]) < 0)) {     // change from strcmp to compare
			j++;
		}
		if (compare(temp, list[j]) > 0) {                           // change from strcmp to compare
			done = 1;					                            // exit if root is larger
		}
		else {
			list[(j+1) / 2-1] = list[j];                            // replace j's parent with list[j]
			j = 2 * j;		                                        // move j to its lchild
		}
	}
	list[(j+1)/ 2-1] = temp;	                                    // move original root to proper place
}

void BUHeapify1(char **list, int i, int n) {
    char *t;
    char *temp;
    int j;
    
    j = i;
    while (2 * (j+1) < n) {                                         // j’s rchild exists
        if (compare(list[2 * j + 1], list[2 * j + 2]) > 0) {        // change from strcmp to compare
            j = 2 * j + 1;                                          // to lchild
        } else {
            j = 2 * j + 2;                                          // to rchild
        }
    }

    if (2 * j+1 <n) {                                               // lchild exits, move to it
        j = 2 * j + 1;
    }

    while (compare(list[i], list[j]) > 0) {                         // change from strcmp to compare
        j = (j - 1) / 2;
    }

    temp = list[j];                                                 // store list[j]
    list[j] = list[i];                                              // move A[i] to A[j]

    while (j > i) {                                                 // move all nodes up along the path
        j = (j - 1) / 2;
        t = list[j];
        list[j] = temp;
        temp = t;
    }
}

void HeapSort(char **list, int n)	                                // in-place heap sort
{
	int i;							                                // index
    char *temp;						                                // temporary word

	for (i = n / 2-1; i >= 0; i--) {	                            // make the list a max heap
		Heapify(list, i, n);
	}
	for (i = n-1 ; i >0; i--) {
        temp = list[i];                                     
		list[i] = list[0];
		list[0] = temp;		                                        // move maximum to the end
		Heapify(list, 0, i);	                                    // restore max heap property to unsorted part
	}
}

void BUHeapSort(char **list, int n)	                                
{
	int i;							                                // index
    char *temp;						                                // temporary word

	for (i = n / 2-1; i >= 0; i--) {	                            // Initialize A[1 : n] to be a max heap
		BUHeapify(list, i, n);
	}
	for (i = n-1 ; i >0; i--) {                                     // Repeat n−1 times
        temp = list[i];                                     
		list[i] = list[0];
		list[0] = temp;		                                        // Move maximum to the end
		BUHeapify(list, 0, i);	                                    // Then make A[1 : i−1] a max heap
	}
}

void HeapSort1(char **list, int n)	                                // in-place heat sort
{
	int i;							                                // index
    char *temp;						                                // temporary word

	for (i = n / 2-1; i >= 0; i--) {	                            // make the list a max heap
		Heapify1(list, i, n);
	}
	for (i = n-1 ; i >0; i--) {
        temp = list[i];                                     
		list[i] = list[0];
		list[0] = temp;		                                        // move maximum to the end
		Heapify1(list, 0, i);	                                    // restore max heap property to unsorted part
	}
}                         

void BUHeapSort1(char **list, int n)	                                
{
	int i;							                                // index
    char *temp;						                                // temporary word

	for (i = n / 2-1; i >= 0; i--) {	                            // Initialize A[1 : n] to be a max heap
		BUHeapify1(list, i, n);
	}
	for (i = n-1 ; i >0; i--) {                                     // Repeat n−1 times
        temp = list[i];                                     
		list[i] = list[0];
		list[0] = temp;		                                        // Move maximum to the end
		BUHeapify1(list, 0, i);	                                    // Then make A[1 : i−1] a max heap
	}
}

void readInput(void)													// read all inputs
{
	int i;											
	char tempWord[1000];												// store input temporarily

	scanf("%d", &N);													// input number of entries
	data = (char **)malloc(sizeof(char *) * N);							// allocate memory for pointers
	for (i = 0; i < N; i++) {
		scanf("%s", tempWord);											// input a word
		data[i] = (char *)malloc(sizeof(char) * (strlen(tempWord) + 1));
		strcpy(data[i], tempWord);										// transfer the input to array
	}
}

double GetTime(void)						                            // get local time in seconds
{
	struct timeval tv;						                            // variable to store time

	gettimeofday(&tv, NULL);				                            // get local time

	return tv.tv_sec + 1e-6 * tv.tv_usec;	                            // return local time in seconds
}

int compare(char *str1, char *str2)
 {
    struct timespec tim = {}, tim2 = {};
    tim.tv_nsec = 10;
    nanosleep(&tim, &tim2);
    return strcmp(str1, str2);
 }

 void printArray(char **A)				                                // print the content of array A
 {
     int i;								                                // index
 
     for (i = 0; i < N; i++) {
         printf("%d %s\n", i + 1, A[i]);                                // print the index and array content
     }
 }

 void copyArray(char **data, char **A)	                                // copy data to array A
{
	int i;								                                // index

	for (i = 0; i < N; i++) {
		A[i] = data[i];					                                // copy content from array data to A
	}
}

int main(void){
    int i;                                                              // loop index
    double t;                                                           // for CPU time tracking

    readInput();                                                        // read input to data array
    A = (char **)malloc(sizeof(char *) * N);
    printf("N = %d\n",N);                                               // print input size
    
    copyArray(data, A);
    t = GetTime();                                                      // initialize time counter
    for (i = 0; i < R; i++) {
        HeapSort(A, N);
    }
    t = (GetTime() - t) / R;                                            // calculate CPU time per iteration
    printf("HeapSort with strcmp: %.5e seconds\n", t);                  // print out CPU time

    copyArray(data, A);
    t = GetTime();                                                      // initialize time counter
    for (i = 0; i < R; i++) {
        BUHeapSort(A, N);
    }
    t = (GetTime() - t) / R;                                            // calculate CPU time per iteration
    printf("BUHeapSort with strcmp: %.5e seconds\n", t);                // print out CPU time

    copyArray(data, A);
    t = GetTime();                                                      // initialize time counter
    for (i = 0; i < R; i++) {
        HeapSort1(A, N);
    }
    t = (GetTime() - t) / R;                                            // calculate CPU time per iteration
    printf("HeapSort with compare: %.9f seconds\n", t);                 // print out CPU time

    copyArray(data, A);
    t = GetTime();                                                      // initialize time counter
    for (i = 0; i < R; i++) {
        BUHeapSort1(A, N);
    }
    t = (GetTime() - t) / R;                                            // calculate CPU time per iteration
    printf("BUHeapSort with compare: %.9f seconds\n", t);               // print out CPU time
    printArray(A);                                                      // print sorted array 
    
}