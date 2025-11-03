// Network Connectivity Problem
// 110191019, YU-TING CHUNG
// 2025/03/24

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

int V, E;                          			// input size
int **data;                    				// input data
int *p;                                     // store disjoint sets
int *R;                                     // store Roots
int Nrepeat = 100;                    		// number of repetitions
int NS;                                     // number of Sets

int SetFind(int i);                         // Find the set that element i is in
int CollapsingFind(int i);                  // Find the root of i, collapsing the elements
int PathHalvingFind(int i);
void SetUnion(int i, int j);                // Form union of two sets with roots, i and j
void WeightedUnion(int i, int j);           // Form union using the weighting rule
void Connect1(void);                        // Find connectivity method 1
void Connect2(void);                        // Find connectivity method 2
void Connect3(void);                        // Find connectivity method 3
void Connect4(void);                        // Find connectivity method 4
void readGraph(void);           			// read all inputs
void printRtable(void);                     // print Root table
double GetTime(void);           			// get local time in seconds


int SetFind(int i){
    while(p[i]>=0){
        i=p[i]; 
    }
    return i;
}

int CollapsingFind(int i){
    int r,s;
    r=i;                                   // Initialized r to i
    while(p[r]>=0){                        // Find the root
        r=p[r];
    }
    while(i!=r){                           // Collapse the elements on the path
        s=p[i]; p[i]=r; i=s;
    }
    return r;
}

int PathHalvingFind(int i){
    int r,s;
    if (p[i]<0){                           // i is a root
        return i;
    }
    r=i; s=p[r];                          // r is the current node; s is its parent
    while(p[s]>0){                        // s is not a root
        p[r]=p[s];                        // reducting path length of r to the root
        r=s; s=p[s];                      // move toward root
    }
    return s;
}

void SetUnion(int i, int j){
    p[i]=j;
}

void WeightedUnion(int i, int j){
    int temp;
    temp=p[i]+p[j];                       // Note that temp < 0
    if(p[i]>p[j]){                        // i has fewer elements
        p[i]=j;
        p[j]=temp;
    }
    else{                                 // j has fewer elements
        p[j]=i;
        p[i]=temp;
    }
}

void Connect1(void)
{
    int i, s0, s1;
    for (i = 0; i < V; i++) {            // One element for each set
        p[i] = -1;
    }
    NS = V;                              // Number of disjoint sets
    for (i = 0; i < E; i++) {            // Connected vertices
        s0 = SetFind(data[i][0] - 1);
        s1 = SetFind(data[i][1] - 1);
        if (s0 != s1) {                  // Unite two sets
            NS--;                        // Number of disjoint sets decreases by 1
            SetUnion(s0, s1);
        }
    }
    for (i = 0; i < V; i++) {           // Record root to R table
        R[i] = SetFind(i) + 1;
    }
}

void Connect2(void)
{
    int i, s0, s1;
    for (i = 0; i < V; i++) {
        p[i] = -1;
    }
    NS = V;
    for (i = 0; i < E; i++) {
        s0 = SetFind(data[i][0] - 1);
        s1 = SetFind(data[i][1] - 1);
        if (s0 != s1) {
            NS--;
            WeightedUnion(s0, s1);      // change to WeightedUnion
        }
    }
    for (i = 0; i < V; i++) {
        R[i] = SetFind(i) + 1;
    }
}

void Connect3(void)
{
    int i, s0, s1;
    for (i = 0; i < V; i++) {
        p[i] = -1;
    }
    NS = V;
    for (i = 0; i < E; i++) {
        s0 = CollapsingFind(data[i][0] - 1);  // change to CollapsingFind
        s1 = CollapsingFind(data[i][1] - 1);  // change to CollapsingFind
        if (s0 != s1) {
            NS--;
            WeightedUnion(s0, s1);
        }
    }
    for (i = 0; i < V; i++) {
        R[i] = SetFind(i) + 1;
    }
}

void Connect4(void)
{
    int i, s0, s1;
    for (i = 0; i < V; i++) {
        p[i] = -1;
    }
    NS = V;
    for (i = 0; i < E; i++) {
        s0 = PathHalvingFind(data[i][0] - 1);  // change to PathHalvingFind
        s1 = PathHalvingFind(data[i][1] - 1);  // change to PathHalvingFind
        if (s0 != s1) {
            NS--;
            WeightedUnion(s0, s1);
        }
    }
    for (i = 0; i < V; i++) {
        R[i] = SetFind(i) + 1;
    }
}

void readGraph(void)            			        // read all inputs
{
	int i;							                // for looping and dynamic store

	scanf("%d %d", &V, &E);					        // read # of Vertices and Edges

	data = (int **)calloc(E, sizeof(int *));	    // initialize data size E * 2
    R = (int *)calloc(V, sizeof(int));              // initialize R table size
    p = (int *)calloc(V, sizeof(int));              // initialize disjoint sets size

    for(i = 0; i < V; i++){
        p[i] = -1;
    }
	for (i = 0; i < E; i++) {                       // Store edges in table
        data[i] = (int *)calloc(2, sizeof(int));
	    scanf("%d %d", &data[i][0], &data[i][1]);	// read each edge
	}
} 

void printRtable(void)                              // print the R table result
{
    int i;
    for (i = 0; i < V; i++) {
        printf("%d ", R[i]);
    }
    printf("\n");
}

double GetTime(void)						        // get local time in seconds
{
	struct timeval tv;						        // variable to store time

	gettimeofday(&tv, NULL);				        // get local time

	return tv.tv_sec + 1e-6 * tv.tv_usec;	        // return local time in seconds
}

int main(){
    int i;
    int Ns1, Ns2, Ns3, Ns4;
    double t0, t1, t2, t3, t4;

    readGraph();
    printf("|V| = %d, |E| = %d\n", V, E);

    t0 = GetTime();
    
    if(V<100000){
        for(i=0; i < Nrepeat; i++){
        Connect1();
        }
    }
    
    t1=GetTime();
    Ns1=NS;
    printf("Connect1 CPU time: %.5e, Disjoint sets: %d\n",(t1-t0)/Nrepeat, Ns1);

    for(i=0; i < Nrepeat; i++){
        Connect2();
    }
    t2=GetTime();
    Ns2=NS;
    printf("Connect2 CPU time: %.5e, Disjoint sets: %d\n",(t2-t1)/Nrepeat, Ns2);

    for(i=0; i < Nrepeat; i++){
        Connect3();
    }
    t3=GetTime();
    Ns3=NS;
    printf("Connect3 CPU time: %.5e, Disjoint sets: %d\n",(t3-t2)/Nrepeat, Ns3);

    for(i=0; i < Nrepeat; i++){
        Connect4();
    }
    t4=GetTime();
    Ns4=NS;
    printf("Connect4 CPU time: %.5e, Disjoint sets: %d\n",(t4-t3)/Nrepeat, Ns4);
}