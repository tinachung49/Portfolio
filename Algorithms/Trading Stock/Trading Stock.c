// Trading Stock
// 110191019, YU-TING CHUNG
// 2025/03/29

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// data structure to store stock info
typedef struct sSTKprice
{
    int year, month, day;
    double price, change;
} STKprice;

int N;                // input size
int R_BF = 1;         // repetition for brute-force approach
int R = 1000;         // repetition for other approachs
STKprice *data;       // array of stock info

void readData(void);  // read stock history
double GetTime(void); // get local time in seconds
double MaxSubArrayBF(int *low, int *high);
double MaxSubArrayBFIm(int *low, int *high);
double Kadane(int *low, int *high);
double MaxSubArray(int begin, int end, int *low, int *high);
double MaxSubArrayXB(int begin, int mid, int end, int *low, int *high);


void readData(void)                                  // read stock history
{
    int i;                                           // for looping

    scanf("%d", &N);                                 // input size
    data = (STKprice *)malloc(sizeof(STKprice) * N); // allocate memory
    for (i = 0; i < N; i++)
    { // input stock info
        scanf("%d", &data[i].year);
        scanf("%d", &data[i].month);
        scanf("%d", &data[i].day);
        scanf("%lf", &data[i].price);
        // calculate price change
        data[i].change = data[i].price - data[(i > 0) * (i - 1)].price;
    }
}

double GetTime(void)         // get local time in seconds
{
    struct timeval tv;       // variable to store time

    gettimeofday(&tv, NULL); // get local time

    return tv.tv_sec + 1e-6 * tv.tv_usec; // return local time in seconds
}

double MaxSubArrayBF(int *low, int *high)
{
    int i, j, k; // loop indices
    double max;  // maximal sum of subarray
    double sum;  // sum of subarray

    max = 0;                             // initialize
    *low = 0;
    *high = N - 1;
    for (j = 0; j < N; j++)              // try all possible subarrays
    { 
        for (k = j; k < N; k++)
        {
            sum = 0;
            for (i = j; i <= k; i++)    // summation for data[j : k].change
            { 
                sum += data[i].change;
            }
            if (sum > max)             // record the maximum value and range
            { 
                max = sum;
                *low = j;
                *high = k;
            }
        }
    }

    return max;
}

double MaxSubArrayBFIm(int *low, int *high)
{
    int i, j = 0;
    double max, sum;

    max = 0; // Initialize
    *low = 0;
    *high = N - 1;

    // Iterate through each possible starting index of subarray
    for (i = 0; i < N; i++)
    {
        sum = 0;
        // Iterate through each possible ending index j starting from i
        for (j = i; j < N; j++)
        {
            sum += data[j].change;  // Add the value of data[j].change to sum

            if (sum > max) // Record the maximum value and range
            { 
                max = sum;
                *low = i;
                *high = j;
            }
        }
    }
    return max;
}

double Kadane(int *low, int *high) 
{ 
    int i, tempLow = 0;  // Loop variable and temporary subarray start index
    double max = 0; // Stores the maximum subarray sum found so far
    double sum = 0; // Stores the current subarray sum
    *low = 0; // Initialize the start index of the maximum subarray
    *high = 0; // Initialize the end index of the maximum subarray
    
    for (i = 0; i < N; i++) // Loop through the array elements
    { 
        // Check if extending the subarray is beneficial 
        if (sum + data[i].change > data[i].change)  
        { 
            sum += data[i].change; // Extend the current subarray
        } 
        else 
        { 
            sum = data[i].change; // Start a new subarray from index i
            tempLow = i; // Update the temporary start index
        } 
        
        // If the current subarray sum is greater than the max found so far
        if (sum > max) 
        { 
            max = sum; 
            *low = tempLow; 
            *high = i;     
        } 
    } 
    
    return max; 
}

double MaxSubArray(int begin, int end, int *low, int *high)
{
    int mid;                                        // middle index
    int llow, lhigh, rlow, rhigh, xlow, xhigh;      // optimal range of subarrays
    double lsum, rsum, xsum;                        // sum of subarrays

    if (begin == end)                               // termination condition
    { 
        *low = begin;
        *high = end;
        return data[begin].change;
    }

    mid = (begin + end) / 2;                          // determine middle index
    lsum = MaxSubArray(begin, mid, &llow, &lhigh);    // left region
    rsum = MaxSubArray(mid + 1, end, &rlow, &rhigh);  // right region
    xsum = MaxSubArrayXB(begin, mid, end, &xlow, &xhigh); // cross boundary

    if (lsum >= rsum && lsum >= xsum)                 // lsum is the largest
    { 
        *low = llow;
        *high = lhigh;
        return lsum;
    }
    else if (rsum >= lsum && rsum >= xsum)           // rsum is the largest
    { 
        *low = rlow;
        *high = rhigh;
        return rsum;
    }
    *low = xlow;
    *high = xhigh;
    return xsum; // cross-boundary is the largest
}

double MaxSubArrayXB(int begin, int mid, int end, int *low, int *high)
{
    int i;
    double lsum, rsum, sum;

    lsum = 0; // initialize for lower half
    *low = mid;
    sum = 0;
    
    for (i = mid; i >= begin; i--) // find low to maximize ∑A[low : mid]
    {
        sum += data[i].change;    // continue to add
        if (sum > lsum)           // record if larger
        { 
            lsum = sum;
            *low = i;
        }
    }

    rsum = 0; // initialize for higher half
    *high = mid + 1;
    sum = 0;
    
    for (i = mid + 1; i <= end; i++)  // find end to maximize ∑A[mid+1 : high]
    {
        sum += data[i].change;        // Continue to add
        if (sum > rsum)               // record if larger
        { 
            rsum = sum;
            *high = i;
        }
    }

    return lsum + rsum; // overall sum
}

int main(void)
{
    int i;                                  // for looping
    int lowBF, highBF;                      // low/high index(brute-force)
    int lowDnC, highDnC;                    // low/high index(divide&conquer)
    int lowBFIm, highBFIm;                  // low/high index (improved)
    int lowKadane, highKadane;              // low/high index (Kadane)
    STKprice *bDayBF, *sDayBF;              // buy/sell day (brute-force)
    STKprice *bDayDnC, *sDayDnC;            // buy/sell day (divide&conquer)
    STKprice *bDayBFIm, *sDayBFIm;          // buy/sell day (improved)
    STKprice *bDayKadane, *sDayKadane;      // buy/sell day (Kadane)
    double earningBF, earningDnC;           // earning of approachs
    double earningBFIm, earningKadane;      // earning of approachs
    double t0, t1, t2, t3, t4;              // time stamp

    readData();                             // read stock history

    t0 = GetTime(); // record time
    for (i = 0; i < R_BF; i++)
    {
        earningBF = MaxSubArrayBF(&lowBF, &highBF);
    }
    t1 = GetTime(); // record time
    for (i = 0; i < R; i++)
    {
        earningDnC = MaxSubArray(0, N - 1, &lowDnC, &highDnC);
    }
    t2 = GetTime(); // record time
    for (i = 0; i < R; i++)
    {
        earningBFIm = MaxSubArrayBFIm(&lowBFIm, &highBFIm);
    }
    t3 = GetTime(); // record time
    for (i = 0; i < R; i++)
    {
        earningKadane = Kadane(&lowKadane, &highKadane);
    }
    t4 = GetTime(); // record time

    // convert the index to the actual buy/sell date
    bDayBF = &data[(lowBF > 0) * (lowBF - 1)];
    sDayBF = &data[highBF];
    bDayDnC = &data[(lowDnC > 0) * (lowDnC - 1)];
    sDayDnC = &data[highDnC];
    bDayBFIm = &data[(lowBFIm > 0) * (lowBFIm - 1)];
    sDayBFIm = &data[highBFIm];
    bDayKadane = &data[(lowKadane > 0) * (lowKadane - 1)];
    sDayKadane = &data[highKadane];

    // print input size, buy/sell date and price and earning of both approaches
    printf("N = %d\n", N);
    printf("Brute-force approach: CPU time %.5e s\n", (t1 - t0) / R_BF);
    printf("  Buy:     %d/%d/%d", bDayBF->year, bDayBF->month, bDayBF->day);
    printf(" at %g\n", bDayBF->price);
    printf("  Sell:    %d/%d/%d", sDayBF->year, sDayBF->month, sDayBF->day);
    printf(" at %g\n", sDayBF->price);
    printf("  Earning: %g per share.\n", earningBF);
    printf("Divide and Conquer: CPU time %.5e s\n", (t2 - t1) / R);
    printf("  Buy:     %d/%d/%d", bDayDnC->year, bDayDnC->month, bDayDnC->day);
    printf(" at %g\n", bDayDnC->price);
    printf("  Sell:    %d/%d/%d", sDayDnC->year, sDayDnC->month, sDayDnC->day);
    printf(" at %g\n", sDayDnC->price);
    printf("  Earning: %g per share.\n", earningDnC);
    printf("Improved brute-force approach: CPU time %.5e s\n", (t3 - t2) / R);
    printf("  Buy:     %d/%d/%d", bDayBFIm->year, bDayBFIm->month, bDayBFIm->day);
    printf(" at %g\n", bDayBFIm->price);
    printf("  Sell:    %d/%d/%d", sDayBFIm->year, sDayBFIm->month, sDayBFIm->day);
    printf(" at %g\n", sDayBFIm->price);
    printf("  Earning: %g per share.\n", earningBFIm);
    printf("Best Algorithm: CPU time %.5e s\n", (t4 - t3) / R);
    printf("  Buy:     %d/%d/%d", bDayKadane->year, bDayKadane->month, bDayKadane->day);
    printf(" at %g\n", bDayKadane->price);
    printf("  Sell:    %d/%d/%d", sDayKadane->year, sDayKadane->month, sDayKadane->day);
    printf(" at %g\n", sDayKadane->price);
    printf("  Earning: %g per share.\n", earningKadane);
    free(data); // release allocated memory

    return 0;
}
