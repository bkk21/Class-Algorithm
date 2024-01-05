#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void swap(double* a, double* b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

int partition(double arr[], int low, int high) {
    double pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(double arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(double arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%f ", arr[i]);
    }
    printf("\n");
}




int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_elements>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Invalid number of elements: %d\n", n);
        return 1;
    }

    // allocate memory for arr
    double *arr = (double*) malloc(n * sizeof(double));
    if (!arr) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // generate n random double values between 0 and 1
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = (double) rand() / RAND_MAX*1000;
    }

    // measure start time
    clock_t start = clock();
    quickSort(arr, 0, n - 1) ;
    // measure end time and calculate elapsed time
    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;

    if (n < 30) {
        printf("Sorted array is: ");
        for (int i = 0; i < n; i++)
            printf("%f \n", arr[i]);
        printf("\n");
    }

    printf("Elapsed time: %f seconds\n", elapsed_time);

    // free memory allocated for arr
    free(arr);

    return 0;
}