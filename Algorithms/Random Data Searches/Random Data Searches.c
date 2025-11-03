//Random Data Searches
//110191019, YU-TING CHUNG
//2025/03/07

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

int N;                          										// input size
int R_AVG = 500;														// number of repetitions of average case
int R_WORST = 5000;														// number of repetitions of worst-case
char **data;                    										// input data

int Search(char *word, char **list, int n);								// Linear Search
int BDSearch(char *word, char **list, int n);							// Bidirection Search
int RDSearch(char *word, char **list, int n);							// Random-direction Search
double GetTime(void);													// get local time in seconds
void readInput(void);													// read all inputs

int Search(char *word, char **list, int n)								// Linear Search
{
	int i;										

	for (i = 0; i < n; i++) {											// compare all possible entries
		if (strcmp(list[i], word) == 0) {								// successfully search
			return i;
		}
	}

	return -1;															// unsuccessfully search
}

int BDSearch(char *word, char **list, int n)							// Bidirection Search
{
	int i;										

	for (i = 0; i < n / 2; i++) {										// compare all entries from both directions
		if (strcmp(list[i], word) == 0) {								// compare words from head
			return i;													// successfully search
		}
		if (strcmp(list[n - i - 1], word) == 0) { 						// compare words from tail
			return n - i - 1;											// successfully search
		}
	}

	return -1;															// unsuccessfully search
}

int RDSearch(char *word, char **list, int n) 							// Random-direction Search
{
	int i, j;
	j = rand() % 2;														//choose j randomly from the set {0, 1} ;
	if (j == 1) {
		for (i = 0; i < n; i++) {										// forward search
			if (strcmp(list[i],word)==0) {								// successfully search
				return i;
			}
		}
	}
	else{
		for (i = n - 1; i >= 0; i--) {									// backward search
			if (strcmp(list[i],word)==0) {								// successfully search
				return i;
			}
		}
	}
	return -1;															// unsuccessfully search
}

double GetTime(){                       								// Calculate to microseconds

	struct timeval tv;

	gettimeofday(&tv, NULL);
	return tv.tv_sec + 1e-6 * tv.tv_usec;	
}

void readInput(void)													// read all inputs
{
	int i;											
	char tmpWord[1000];													// store input temporarily

	scanf("%d", &N);													// input number of entries
	data = (char **)malloc(sizeof(char *) * N);							// allocate memory for pointers
	for (i = 0; i < N; i++) {
		scanf("%s", tmpWord);											// input a word
		data[i] = (char *)malloc(sizeof(char) * (strlen(tmpWord) + 1));
		strcpy(data[i], tmpWord);										// transfer the input to array
	}
}

int main(void) {
    int i, j, result = 0;   											// loop index and search result
    double t;               											// for CPU time tracking

    readInput();             											// read input data
    printf("n: %d\n", N);    											// print N

    // Linear Search (average case)
    t = GetTime();														// initialize time counter
    for (i = 0; i < R_AVG; i++) {										// search item
        for (j = 0; j < N; j++) {    
            result = Search(data[j], data, N);
        }
    }
    t = (GetTime() - t) / (R_AVG * N); 									// calculate CPU time / iteration
    printf("Linear search average CPU time: %.5e\n", t);				// print out CPU time

    // Bidirectional Search (average case)
    t = GetTime();														// initialize time counter
    for (i = 0; i < R_AVG; i++) {                                       // search item
        for (j = 0; j < N; j++) {
            result = BDSearch(data[j], data, N);
        }
    }
    t = (GetTime() - t) / (R_AVG * N);
    printf("Bidirection search average CPU time: %.5e\n", t);           // print out CPU time

    // Random-direction Search (average case)
    t = GetTime();                                                      // initialize time counter
    for (i = 0; i < R_AVG; i++) {                                       // search item
        for (j = 0; j < N; j++) {
            result = RDSearch(data[j], data, N);
        }
    }
    t = (GetTime() - t) / (R_AVG * N);                                  // calculate CPU time per iteration
    printf("Random-direction search average CPU time: %.5e\n", t);      // print out CPU time

    // Linear Search (worst-case)
    t = GetTime();                                                      // initialize time counter
    for (i = 0; i < R_WORST; i++) {                                     // search item
        for (j = 0; j < N; j++) {
            result = Search(data[N-1], data, N);  						// search for the last one
        }
    }
    t = (GetTime() - t) / (R_WORST * N);                                // calculate CPU time per iteration
    printf("Linear search worst-case CPU time: %.5e\n", t);             // print out CPU time

    // Bidirectional Search (worst-case)
    t = GetTime();                                                      // initialize time counter
    for (i = 0; i < R_WORST; i++) {                                     // search item
        for (j = 0; j < N; j++) {
            result = BDSearch(data[N/2], data, N); 						// search for the middle one
        }
    }
    t = (GetTime() - t) / (R_WORST * N);                                // calculate CPU time per iteration
    printf("Bidirection search worst-case CPU time: %.5e\n", t);        // print out CPU time

    // Random-direction Search (worst-case)
    t = GetTime();                                                      // initialize time counter
    for (i = 0; i < R_WORST; i++) {                                     // search item
        for (j = 0; j < N; j++) {
            result = RDSearch(data[N-1], data, N); 						// search for the last one
        }
    }
    t = (GetTime() - t) / (R_WORST * N);                                // calculate CPU time per iteration
    printf("Random-direction search worst-case CPU time: %.5e\n", t);   // print out CPU time

    return 0;
}
