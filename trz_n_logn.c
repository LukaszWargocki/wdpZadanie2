#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>

void free2DArray(int** a, int m);
int new_min_challenger(int a, int b, int c);
int new_max_challenger(int a, int b, int c);
int max_int(int a, int b);
int min_int(int a, int b);

// driver code
int main() {
  // liczba wierszy i kolumn
  int rows, cols = 2;
  // czytaj ilość wierszy z wsadu
  scanf("%d", &rows);
  // zbuduj tablicę n
  int** arr = malloc((long long unsigned int) rows * sizeof(int*));
  for (int i = 0; i < rows; i++) {
    arr[i] = malloc((long long unsigned int) cols * sizeof(int));
  }
  for (int i = 0; i < rows; i++) {
    scanf("%d %d", &arr[i][0], &arr[i][1]);
  };
    for (int i = 0; i < rows; i++) {
    printf("%d ", arr[i][0]);
    printf("%d\n", arr[i][1]);
  };
  int min_odleglosc = INT_MAX;
  int max_odleglosc = -1;
  for (int i = 0, j = 1, k = 2; i < rows; i++) {
    if (arr[i][0] == arr[j][0]) { // jeżeli B jest tej samej sieci do A przesuń B i C
      j++;
      k++;
    } else if (arr[i][0] == arr[k][0]) { // jeżeli A i C są tej samej sieci przesuń C
      k++;
    } else if (arr[j][0] == arr[k][0]) { // jeżeli B i C są tej samej sieci przesuńC
      k++;
    }
  }
  free2DArray(arr, rows);
  printf("\n7 = %d\n10 = %d\n", min_odleglosc, max_odleglosc);
  return 0;
}

// zwolnij pamięć dwuwymiarowej tablicy integerów o m wierszach
void free2DArray(int** a, int m) {
  for (int i = 0; i < m; i++) {
    free(a[i]);
  }
  free(a);
}

int new_min_challenger(int a, int b, int c) {
  return max_int(abs(a - b), abs(b - c));
}
int new_max_challenger(int a, int b, int c) {
  return min_int(abs(a - b), abs(b - c));
}
int max_int(int a, int b) {
  return a > b ? a : b;
}
int min_int(int a, int b) {
  return a < b ? a : b;
}