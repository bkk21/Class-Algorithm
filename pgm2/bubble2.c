#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubbleSort(double arr[], int n) {
    int i, j;
    double temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // swap arr[j] and arr[j+1]
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int n;
    clock_t start, end;
    double cpu_time_used;
    if (argc != 2) {
        printf("Usage: %s <size of array>\n", argv[0]);
        return 1;
    }
    n = atoi(argv[1]); // convert string argument to integer
    
    double *arr = (double*) malloc(n * sizeof(double));
    if (arr == NULL) {
        printf("Error: Failed to allocate memory for array.\n");
        return 1;
    }
    
    srand(time(NULL)); // seed for random number generator
    
    // populate array with random doubles
    for (int i = 0; i < n; i++) {
        arr[i] = (double) rand() / RAND_MAX * 1000.0;
    }
    
    start = clock(); // start timer
    bubbleSort(arr, n);
    end = clock(); // end timer
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    printf("Sorted array: ");
    for (int i=0; i < n; i++) {
        printf("%.2f ", arr[i]);
    }
    
    printf("\nElapsed time: %f seconds\n", cpu_time_used);
    
    free(arr); // deallocate memory
    return 0;
}
