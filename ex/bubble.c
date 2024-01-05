#include <stdio.h>
#include <stdlib.h>
#include <time.h>
double toc(double tstart) ;
#define DTYPE   double
#define SWAP(aa,bb) { DTYPE  tmp; tmp=aa; aa=bb; bb=tmp;}
DTYPE *mk_rand_data(int N);
void bubblesort( DTYPE arr[], int N);

int main(int argc, char *argv[])
{
    DTYPE *arr;
    double tstart;
    int N;
    N = atoi(argv[1]);
    srand(time(NULL));
    arr=mk_rand_data( N );
    printf("\n sort .... \n");
    tstart=clock();
    bubblesort(arr, N);
    printf("bubble:%f\n", toc(tstart));
#if 0
    for(i = 0; i < N ; i++)
       printf("%f \n", arr[i]);
#endif
        return 0;
}

double toc(double tstart) {
        return (clock() - tstart) / CLOCKS_PER_SEC;
}

DTYPE *mk_rand_data(int N)
{
        DTYPE *arr = (DTYPE *) malloc(sizeof(DTYPE) * N);
        for(int i = 0; i < N; i++)
        arr[i] = rand() /(DTYPE) RAND_MAX;
    return arr;
}

void bubblesort(DTYPE arr[], int N)
{
        int i,  k;
        for (k = 1; k <= N - 1; k++){
            for (i = 0; i < N - k; i++)
                if (arr[i + 1] < arr[i]){
                     SWAP(arr[i + 1], arr[i]);
                }
    }
}
