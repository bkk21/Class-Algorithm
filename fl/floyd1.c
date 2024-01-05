#include <stdio.h>

int main() {
  int N, i, j, k, tmp;
  int D[100][100], Path[100][100];

  // Get the number of vertices.
  scanf("%d", &N);

  // Initialize the distance matrix.
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      if (i == j) {
        D[i][j] = 0;
      } else {
        D[i][j] = INT_MAX;
      }
    }
  }

  // Initialize the path array.
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      Path[i][j] = -1;
    }
  }

  // Run Floyd-Warshall algorithm.
  for (k = 0; k < N; k++) {
    for (i = 0; i < N; i++) {
      if (i == k) {
        continue;
      }
      for (j = 0; j < N; j++) {
        if (j == k || j == i) {
          continue;
        }
        if (D[i][k] != INT_MAX && D[k][j] != INT_MAX) {
          tmp = D[i][k] + D[k][j];
          if (tmp < D[i][j]) {
            D[i][j] = tmp;
            Path[i][j] = k;
          }
        }
      }
    }
  }

  // Print the distance matrix.
  printf("The distance matrix:\n");
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      printf("%3d ", D[i][j]);
    }
    printf("\n");
  }

  // Print the paths.
  printf("The paths:\n");
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      if (i != j) {
        print_path(i, j);
      }
    }
  }

  return 0;
}

void print_path(int i, int j) {
  if (Path[i][j] == -1 || i == j) {
    return;
  }

  printf("%3d :", D[i][j]);
  printf("%d", i);
  while (i != j) {
    i = Path[i][j];
    printf("-> %d", i);
  }
  printf("\n");
}

