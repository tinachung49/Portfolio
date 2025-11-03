//Basic Sorts
//110191019, YU-TING CHUNG

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

int N;                                  // input size
int R = 500;                            // number of repetitions
char **data;                            // input data
char **A;                               // array to be sorted

double GetTime(void);                   // get local time in seconds
void readInput(void);                   // read all inputs
void printArray(char **A);              // print the content of array A
void copyArray(char **data, char **A);  // copy data to array A
void SelectionSort(char **list, int n); // in-place selection sort
void InsertionSort(char **list, int n); // in-place insertion sort
void BubbleSort(char **list, int n);    // in-place bubble sort
void minMaxSort(char **list,int n);     // in-place minMax sort

double GetTime(){                       // Calculate to microseconds

	struct timeval tv;

	gettimeofday(&tv, NULL);
	return tv.tv_sec + 1e-6 * tv.tv_usec;	
}

void readInput(void)                    // read all inputs
{
    scanf("%d", &N);
    int i;
    
    data = (char **)calloc(N, sizeof(char *));
    A = (char **)calloc(N, sizeof(char *));

    for (i = 0; i < N; i++){
        data[i] = (char *)calloc(500, sizeof(char));
        A[i] = (char *)calloc(500, sizeof(char));
        scanf("%s", data[i]);
    }

}           

void printArray(char **A)               // print the content of array A
{
    int i, j;
    for (i = 0; i < N; i++){
        printf("%s\n", A[i]);
    }

}

void copyArray(char **data, char **A)   // copy data to array A
{
    int i;
    
    for (i = 0; i < N; i++){
        strcpy(A[i], data[i]);
    }
}

void SelectionSort(char **list,int n){                  

    int i, j, k;                                        
	char *temp;

	for(i = 0; i <= N-1; i++){                              //for every A[i]            
        j=i;				                                //Initialize j to i
		for(k=i+1; k < n; k++){				                //Search for the smallest in A[i+1:n]
			if(strcmp(list[k], list[j]) < 0){               //Found, remember it in j
                j = k;			
			}                                           
		}                                               
        temp = list[i];                                     //Swap A[i] and A[j]
		list[i] = list[j];
		list[j] = temp;                                 
	}    
}

void InsertionSort(char **list,int n){                      
    int i, j;
    char *temp;
    for (j = 1; j < N; j++){                                // Assume A[1 : j −1] already sorted.
        temp = list[j];                                     // Move A[j] to its proper place.
        i = j - 1;                                          // Init i to be j −1.
        while((i >= 0) && (strcmp(temp, list[i]) < 0)){     // Find i such that A[i] ≤ A[j].
            list[i + 1] = list[i];                          // Move A[i] up by one position.
            i = i - 1;
        }
        list[i + 1] = temp;                                 // Move A[j] to A[i+1].
    }
}

void BubbleSort(char **list,int n){
    int i, j;
	char *temp;
	
	for(i = 0; i <= N-1; i++){			                    // Find the smallest item for A[i], 1 ≤ i ≤ n−1		
		for(j = 0; j <N-1-i; j++){				            // search among A[i:n]
			if(strcmp(list[j], list[j+1])>0){	            // Swap A[j] and A[j −1], if A[j] < A[j −1]
				temp = list[j];
				list[j] = list[j+1];
				list[j+1] = temp;
			}                                           
		}
	}
}

void minMaxSort(char **list,int N) {
    int i;
    int l=0;                                               // init l and h
    int h=N-1;
    char *temp;

    while(l<h){                                            // sort A[l : h]
        int imin=l;                                        // find min and max in A[l : h]
        int imax=h;

        if (strcmp(list[h],list[l])<0){                    // ensure A[h] >= A[l]
            temp=list[l];
            list[l]=list[h];
            list[h]=temp;
            }

        for(i=l+1;i<h;i++){
            if (strcmp(list[i], list[imin])<0){
                imin=i;
            }

            else if(strcmp(list[i],list[imax])>0){
                imax=i;
            }
        }
        if(imin>l){                                        // set A[l] = min
            temp=list[l];
            list[l]=list[imin];
            list[imin]=temp;
        }
        if(imax<h){                                        // set A[h] = max
            temp=list[h];
            list[h]=list[imax];
            list[imax]=temp;
        }
        l=l+1;                                             // reduce sorting range
        h=h-1;
    }
}

int main(void)
{
    int i;                                                               // loop index
    double t;                                                            // for CPU time tracking

    readInput();                                                         // read input to data array
    printf("N=%d\n",N);                                                  // print input size

    t = GetTime();                                                       // initialize time counter
    for (i = 0; i < R; i++) {
        copyArray(data, A);                                              // initialize array for sorting
        SelectionSort(A, N);                                             // execute selection sort
    }
    t = (GetTime() - t) / R;                                             // calculate CPU time per iteration
    printf("Selection sort: %.8e seconds\n", t);                         // print out CPU time

    t = GetTime();                                                       // initialize time counter
    for (i = 0; i < R; i++) {
        copyArray(data, A);                                              // initialize array for sorting
        InsertionSort(A, N);                                             // execute insertion sort
    }
    t = (GetTime() - t) / R;                                             // calculate CPU time per iteration
    printf("Insertion sort: %.8e seconds\n", t);                         // print out CPU time

    t = GetTime();                                                       // initialize time counter
    for (i = 0; i < R; i++) {
        copyArray(data, A);                                              // initialize array for sorting
        BubbleSort(A, N);                                                // execute bubble sort
    }
    t = (GetTime() - t) / R;                                             // calculate CPU time per iteration
    printf("Bubble sort: %.8e seconds\n", t);                            // print out CPU time

    t = GetTime();                                                       // initialize time counter
    for (i = 0; i < R; i++) {
        copyArray(data, A);                                              // initialize array for sorting
        minMaxSort(A, N);
    }
    t = (GetTime() - t) / R;                                             // calculate CPU time per iteration
    printf("Min-max sort: %.8e seconds\n", t);                           // print out CPU time

    printArray(A);                                                       // print sorted results

    for (int i = 0; i < N; i++) {
        free(data[i]);
        free(A[i]);
    }
    free(data);
    free(A);

    return 0;
}
