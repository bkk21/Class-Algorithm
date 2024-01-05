#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shellsort(int arr[], int N);
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

    printf("shell: %f\n", toc(tstart));

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

void shellsort(int arr[], int N)
{
    int i, j, k, h, cur_el;
    int ciura_gap_sequence[] = { 701, 301, 132, 57, 23, 10, 4, 1 };
    int gap_sequence_length = sizeof(ciura_gap_sequence) / sizeof(ciura_gap_sequence[0]);

    for(k = 0; k < gap_sequence_length; k++)
    {
        h = ciura_gap_sequence[k];
        for (i = h; i < N; i++)
        {
            cur_el = arr[i]; //정렬 안 된 부분의 가장 왼쪽 원소
            j = i - h; //정렬된 부분의 가장 오른쪽 원소 위치

            while((j >= 0) && (arr[j]) > cur_el)
            {
                arr[j + h] = arr[j]; //현재 원소가 j위치에 삽입 가능
                j = j - h;
            }
            arr[j + h] = cur_el;
        }
    }
}
