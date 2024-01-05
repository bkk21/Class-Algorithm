#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(double arr[], int N);
double toc(double tstart);
double *mk_rand_data(int N);

#define DTYPE double
#define SWAP(aa, bb) { DTYPE tmp; tmp = aa; aa = bb; bb = tmp;}

int main(int argc, char * argv[])
{
    double *arr, tstart;
    int N, i;

    N = atoi(argv[1]);
    srand(clock());
    arr = mk_rand_data( N );

    printf(".... sort .... \n");

    tstart = clock();
    selectionSort(arr, N);
    printf("selection: %f\n", toc(tstart));

    return 0;
}

double toc(double tstart)
{
    return (clock() - tstart) / CLOCKS_PER_SEC;
}

double* mk_rand_data(int N)
{
    double *arr = (double *) malloc( sizeof(double) * N);

    for(int i = 0; i < N; i++)
        arr[i] = rand() / (double) RAND_MAX;
    
    return arr;
}

void selectionSort(double arr[], int N)
{
    int i, j, min_idx;

    for (i = 0; i < N-1; i++) {
        min_idx = i;
        for (j = i+1; j < N; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        SWAP(arr[i], arr[min_idx]);
    }
}

