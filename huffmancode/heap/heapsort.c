/*
    왼쪽 자식과 오른쪽 자식의 관계가 있다
    각 레별 순서로 넣는다
    책 연습문제 270쪽 33번

             90 
         30      50 
      20   40  60   80 
    60  70

    모두 다 차면 전채 원소의 개수는 2^4 - 1 개
    힙을 만들 때 제일 끝부터 자식이 있는지 없는지를 따진다
    배열 상에서 맨 마지막 줄을 뺸 마지막에서 시작
    각각 비교 역순으로 살펴간다

    가장 맨 아래를 최 상단으로 올림 

    시험때는 일차원 배열로 적기 
    계산만 트리로 한다

    단점은 운영체제 사이의 단점임

    log(n!) = log 1 + log 2 + log 3 + ... + log n 

    정렬은 O(nlogn)보다 개선할 순는 없다

    개선은 없을지 몰라도 상한 하한 시 상수를 줄일 수 있다!

    갭 시퀀스 히바드 정도? 더 좋은 게 있는지 찾아보기 
    

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shellSort(double arr[], int n);
#include <stdio.h>

// Function to heapify a subtree rooted at node i
void heapify(double arr[], int n, int i)
{
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // left child
    int right = 2 * i + 2; // right child

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        // swap arr[i] with arr[largest]
        double temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // recursively heapify the affected subtree
        heapify(arr, n, largest);
    }
}

void heapSort(double arr[], int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i >= 0; i--) {
        // Move current root to end
        double temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}


int main(int argc, char *argv[]) {
    // Check if the number of arguments is correct
    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return 1;
    }

    // Parse the size of the array from the command-line argument
    const int n = atoi(argv[1]);

    // Seed the random number generator
    srand(time(NULL));
    // Generate an array of random doubles
    double *arr=(double*) malloc(n*sizeof(double));//[n];
    for (int i = 0; i < n; i++) {
        arr[i] = (double) rand() / RAND_MAX * 1000.0;
    }
    // Sort the array using shellSort()
    printf("Sorting %d values...\n", n);
    clock_t start = clock();
    heapSort(arr, n);
    clock_t end = clock();
    double elapsed = (double) (end - start) / CLOCKS_PER_SEC;

    // Print the sorted data if n is less than 30
    if (n < 30) {
        printf("Sorted data:\n");
        for (int i = 0; i < n; i++) {
            printf("%.2f ", arr[i]);
        }
        printf("\n");
    }

    printf("Sorting took %.4f seconds.\n", elapsed);

    return 0;
}
void shellSort(double arr[], int n) {
    int gaps[] = {16577, 4193, 1073, 281, 77, 23, 8, 1};
    int ngaps = 8;

    for (int i = 0; i < ngaps; i++) {
        int gap = gaps[i];
        for (int j = gap; j < n; j++) {
            double temp = arr[j];
            int k;
            for (k = j; k >= gap && arr[k - gap] > temp; k -= gap) {
                arr[k] = arr[k - gap];
            }
            arr[k] = temp;
        }
    }
}