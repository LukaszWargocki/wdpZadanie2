#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>

// deklaracja funkcji pomocniczych
void free2DArray(int** a, int m);
int kandydat_min3(int a, int b, int c);
int kandydat_max3(int a, int b, int c);
int max_int(int a, int b);
int min_int(int a, int b);

int main() {
  // zmienne przechowujące liczbę wierszy i kolumn wsadu
  int rows, cols = 2;
  // odczytuje z pojedynczego inputu liczbę wierszy dalszej części inputu
  scanf("%d", &rows);
  // zbuduj tablicę 2D o odczytanej ilości wierszy
  int** arr = malloc((long long unsigned int) rows * sizeof(int*));
  for (int i = 0; i < rows; i++) {
    arr[i] = malloc((long long unsigned int) cols * sizeof(int));
  }
  // wypełnij tablicę inpute,
  for (int i = 0; i < rows; i++) {
    scanf("%d %d", &arr[i][0], &arr[i][1]);
  };
  // wyświetl input
    for (int i = 0; i < rows; i++) {
    printf("%d ", arr[i][0]);
    printf("%d\n", arr[i][1]);
  };
  // zainicjalizuj zmienne do przechowywania wyników najgorszymi wartościami
  int min_odleglosc = INT_MAX;
  int max_odleglosc = -1;
  // sprawdź wszystkie możliwe kombinacje trzech punktów
  for (int i = 0; i < rows; i++) {
    for (int j = i + 1; j < rows; j++){
      for (int k = j + 1; k < rows; k++){
        if (arr[i][0] != arr[j][0] && arr[i][0] != arr[k][0] && arr[j][0] != arr[k][0] && i < j && j < k) {
          min_odleglosc = min_int(min_odleglosc, kandydat_min3(arr[i][1], arr[j][1], arr[k][1]));
          max_odleglosc = max_int(max_odleglosc, kandydat_max3(arr[i][1], arr[j][1], arr[k][1]));
        }
      }
    }
  }
  // zwolnij pamięć
  free2DArray(arr, rows);
  // zestaw znany wynik dla domyślnego inputu z uzyskanym
  printf("\n7 = %d\n10 = %d\n", min_odleglosc, max_odleglosc);
  return 0;
}

// zwolnia pamięć dwuwymiarowej tablicy integerów o m wierszach
void free2DArray(int** a, int m) {
  for (int i = 0; i < m; i++) {
    free(a[i]);
  }
  free(a);
}

// przyjmuje trzy integery reprezentujące odległości punktów od początku i zwaraca dłuższy z odcinków pomiędzy nimi; kolejność argumentów ma znaczenie
int kandydat_min3(int a, int b, int c) {
  return max_int(abs(a - b), abs(b - c));
}

// przyjmuje trzy integery reprezentujące odległości punktów od początku i zwaraca krótszy z odcinków pomiędzy nimi; kolejność argumentów ma znaczenie
int kandydat_max3(int a, int b, int c) {
  return min_int(abs(a - b), abs(b - c));
}

// dwa integery argmenty, zwraca większy z nich
int max_int(int a, int b) {
  return a > b ? a : b;
}

// dwa argumenty integery, zwraca mniejszy z nich
int min_int(int a, int b) {
  return a < b ? a : b;
}