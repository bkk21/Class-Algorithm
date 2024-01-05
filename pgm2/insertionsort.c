#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubblesort(int arr[], int N);
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

    printf("insertion: %f\n", toc(tstart));

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

int insertionsort(int arr[], int N)
{
	int i, j, cur_el;
	for(i = 1; i < N; i++)
	{
		j = 1;
		cur_el = arr[j]; //정렬 안 된 부분의 가장 왼쪽 원소
		while( (j <= arr[j - 1]) && ( arr[j - 1] > cur_el) ) 
		{
			arr[j] = arr[j-1]; //현재 원소가 J위치에 삽입 가능
			j--; //num_op++;
		}
		arr[j] = cur_el;
	}
}
