#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>

void free2DArray(int** a, int m);
int kandydat_min3(int a, int b, int c);
int kandydat_max3(int a, int b, int c);
int max_int(int a, int b);
int min_int(int a, int b);

// driver
int main() {
  // liczba wierszy i kolumn w tablicy
  int liczbaHoteli, kolumny = 4;

  // odczytaj ilość wierszy z wejścia
  scanf("%d", &liczbaHoteli);
  /* zbuduj dwuwymarową tablicę:
    w pierwszej kolumnie będzie przechowywać identyfikator sieci
    w drugiej - odległość od początku trasy - kilometraż
    w trzeciej indeks najbliższego hotelu innej sieci o niższym indeksie/kilometrażu (hotel A)
    w czwartej indeks najbliższego hotelu innej sieci o wyższym indeksie/kilometrażu (hotel C)
  */
  int **hotele = malloc((size_t) liczbaHoteli * sizeof(int*));
  for (int i = 0; i < liczbaHoteli; i++) {
    hotele[i] = malloc((size_t) kolumny * sizeof(int));
  }

  // populuj pierwszą kolumnę tablicy identyfikatorami sieci, drugą kolumnę kilometrażami z wejścia
  for (int i = 0; i < liczbaHoteli; i++) {
    scanf("%d %d", &hotele[i][0], &hotele[i][1]);
  }

  // wstaw indeksy spoza tablicy najbliższej wcześniejszą sieci dla pierwszego hotelu i najbliższej dalszej dla ostatniego
  hotele[0][2] = -1;
  hotele[liczbaHoteli - 1][3] = liczbaHoteli;

  // populuj trzecią kolumnę tablicy - nabliższe wcześniejsze hotele innej sieci
  // zaczynamy od drugiego i porównujemy z bliższym poprzednikiem
  for (int i = 1; i < liczbaHoteli; i++) {
      // porównaj sieć obecnego z poprzednim; inne? wpisz indeks poprzedniego te same? wpisz wartość poprzedniego
      hotele[i][2] = (hotele[i][0] != hotele[i - 1][0]) ? i - 1 : hotele[i - 1][2];
  }

  // populuj czwartą kolumnę tablicy - najbliższe dalsze hotele innej sieci
  for (int i = liczbaHoteli - 2; i >= 0; i--) {
    // podobnie jak wyżej, zaczynij od przedostatniego i porównuj z dalszym poprzednikiem
    hotele[i][3] = (hotele[i][0] != hotele[i + 1][0]) ? i + 1 : hotele[i + 1][3];
  }

  // weryfikacja danych z przykładu - WYWAL
  for (int i = 0; i < liczbaHoteli; i++) {
    printf("%d ", hotele[i][0]);
    printf("%d\n", hotele[i][1]);
    printf("%d\n", hotele[i][2]);
    printf("%d\n", hotele[i][3]);
  }

  // zainicjalizuj zmienne wynikowe z wartościami zawsze zastępowanymi przez funkcje ewaluujące kandydatów
  int najblizsze3 = INT_MAX;
  int najdalsze3 = -INT_MAX;

  // szukaj najbliższej trójki hoteli innych sieci, hotel o bieżącym indeksie jest hotelem B w max(B - A, C - B)
  for (int i = 1; i < liczbaHoteli - 1; i++) {
    // odczytaj indeksy najbliższych sąsiednich hoteli innych sieci - A, B
    int indeksA = hotele[2][i];
    int indeksC = hotele[3][i];
    // nie wykonuj dla indeksów spoza tablicy - wszystkie poprzednie/wszystke dalsze są tej samej sieci co bieżący
    if (indeksA >= 0 && indeksC < liczbaHoteli) {
      int siecA = hotele[indeksA][0];
      int siecC = hotele[indeksC][0];
      // nie wykonuj jeżeli najbliższy poprzedni jest tej samej sieci co najbliższy dalszy
      if (siecA != siecC) {
        // odczytaj odległości od początku, oblicz większy odcinek i zaktualizuj wynik
        int kilometrA = hotele[indeksA][1];
        int kilometrC = hotele[indeksC][1];
        int kilometrB = hotele[i][1];
        najblizsze3 = min_int(najblizsze3, max_int(kilometrB - kilometrA, kilometrC - kilometrB));
      }
    }
  }
  // szukaj najdalszej trójki hoteli innych sieci, hotel o bieżącym indeksie jest hotelem B w min(B - A, C - B)
  for (int ) {
    
  }

  // zwolnij pamięć tablicy
  free2DArray(hotele, liczbaHoteli);

  // weryfikacja wyniku z przykładu WYWAL
  printf("\n7 = %d\n10 = %d\n", najblizsze3, najdalsze3);

  return 0;
}

// pomocnicza funkcja zwalniająca pamięć dwuwymiarowej tablicy integerów o zadanej liczbie wierszy
void free2DArray(int** a, int wiersze) {
  for (int i = 0; i < wiersze; i++) {
    free(a[i]);
  }
  free(a);
}

// pomocnicza funkcja -> fmax dla integerów
int max_int(int a, int b) {
  return a > b ? a : b;
}

// pomocnicza funkcja -> fmin dla integerów
int min_int(int a, int b) {
  return a < b ? a : b;
}