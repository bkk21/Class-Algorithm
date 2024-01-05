#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(double arr[], double left[], int left_len, 
                         double right[], int right_len) {
    int i = 0, j = 0, k = 0;

    while (i < left_len && j < right_len) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < left_len) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < right_len) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void merge_sort(double arr[], int len) {
    if (len < 2) {
        return;
    }

    int mid = len / 2;
    double *left=(double *) malloc(mid*sizeof(double));
    double *right=(double *) malloc((mid+1)*sizeof(double));
    
    for (int i = 0; i < mid; i++) {
        left[i] = arr[i];
    }

    for (int i = mid; i < len; i++) {
        right[i - mid] = arr[i];
    }

    merge_sort(left, mid);
    merge_sort(right, len - mid);

    merge(arr, left, mid, right, len - mid);
    free(left); free(right);
}
// main function to perform heap sort
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
    merge_sort(arr, n);
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

