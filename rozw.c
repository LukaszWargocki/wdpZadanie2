#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

void free2DArray(int** a, int wiersze);
int maxInt(int a, int b);
int minInt(int a, int b);

// driver
int main() {
  // liczba wierszy i kolumn w tablicy
  int liczbaHoteli, kolumny = 4;

  // odczytaj ilość wierszy z wejścia
  scanf("%d", &liczbaHoteli);
  /* zbuduj dwuwymarową tablicę:
    w pierwszej kolumnie będzie przechowywać identyfikator sieci
    w drugiej - odległość od początku trasy - kilometraż
    w trzeciej indeks najbliższego hotelu innej sieci o niższym indeksie/kilometrażu (wcześniejszym)
    w czwartej indeks najbliższego hotelu innej sieci o wyższym indeksie/kilometrażu (dalszym)
  */

  int **hotele = malloc((size_t) liczbaHoteli * sizeof(int*));
  for (int i = 0; i < liczbaHoteli; i++) {
    hotele[i] = malloc((size_t) kolumny * sizeof(int));
  }

  // populuj pierwszą kolumnę tablicy identyfikatorami sieci, drugą kolumnę kilometrażami z wejścia
  for (int i = 0; i < liczbaHoteli; i++) {
    scanf("%d %d", &hotele[i][0], &hotele[i][1]);
  }

  // sprawdzenie czy istnieją trzy rózne sieci
  int indeksSieci1 = 0;
  int indeksSieci2 = 1;

  // inkrementuj aż znajdzie inną sieć lub dojdzie do końca
  while (hotele[indeksSieci1][0] == hotele[indeksSieci2][0] && indeksSieci2 < liczbaHoteli)
    indeksSieci2++;
  int indeksSieci3 = indeksSieci2 + 1;
  while ((hotele[indeksSieci3][0] == hotele[indeksSieci2][0] || hotele[indeksSieci3][0] == hotele[indeksSieci1][0])
          && indeksSieci3 < liczbaHoteli)
    indeksSieci3++;
  
  // jeżeli nie znaleziono trzeciej sieci wyświetl "0 0" i zakończ
  if (indeksSieci3 >= liczbaHoteli) {
    printf("0 0");
    return 0;
  }

  // wstaw indeksy spoza tablicy najbliższej wcześniejszej sieci dla pierwszego hotelu i najbliższej dalszej dla ostatniego
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

  // zainicjalizuj zmienne wynikowe z wartościami zawsze zastępowanymi przez funkcje ewaluujące kandydatów
  int najblizsze3 = INT_MAX;
  int najdalsze3 = -INT_MAX;

  // szukaj najbliższej początku trójki hoteli innych sieci, hotel o bieżącym indeksie jest hotelem B w max(B - A, C - B)
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
        najblizsze3 = minInt(najblizsze3, maxInt(kilometrB - kilometrA, kilometrC - kilometrB));
      }
    }
  }
  // szukaj najdalszej trójki hoteli innych sieci
  // porównaj trzy najwcześniejsze hotele różnych sieci i trzy najdalsze hotele różnych sieci z hotelami innych sieci pomiędzy nimi - pesymistycznie złożoność 9 * n
  // wybierz pierwszy hotel jako pierwszego kandydata na hotel A
  int indeksA1 = 0;
  int siecA1 = hotele[indeksA1][0];
  // jeżeli pierwszy kandydat nie ma hotelu innej sieci na prawo, ustaw ten sam hotel jako drugiego kandydata
  int indeksA2 = hotele[indeksA1][3] == liczbaHoteli ? 0 : hotele[indeksA1][3];
  int siecA2 = hotele[indeksA2][0];
  // zainicjalizuj trzeciego kandydata jako drugiego kandydata
  int indeksA3 = indeksA2;

  // szukaj trzeciego kandydata wzdłuż drogi aż znajdziesz hotel innej sieci niż poprzedni kandydaci (albo dojdziesz do końca)
  while ((hotele[indeksA3][0] == siecA1 || hotele[indeksA3][0] == siecA2) && indeksA3 < liczbaHoteli - 1)
    indeksA3++;
  // zainicjalizuj pierwszego kandydata na hotel C jako ostatni hotel
  int indeksC1 = liczbaHoteli - 1;
  int siecC1 = hotele[indeksC1][0];
  // jeżeli pierwszy kandydat nie ma hotelu innej sieci na lewo zainicjalizuj drugiego kandydata jako ten sam hotel
  // jeżeli ma, zainicjalizuj drugiego kandydata jako pierwszy hotel innej sieci na lewo
  int indeksC2 = hotele[indeksC1][2] == - 1 ? indeksC1 : hotele[indeksC1][2];
  int siecC2 = hotele[indeksC2][0];
  // szukaj trzeciego kandydata na lewo, aż nie dojdziesz do początku tablicy 
  // lub nie znajdziesz hotelu innej sieci niż poprzedni kandydaci
  int indeksC3 = indeksC2;
  while ((hotele[indeksC3][0] == siecC1 || hotele[indeksC3][0] == siecC2) && indeksC3 > 0)
    indeksC3++;
  // zapisz kandydatów w iterowalnej postaci
  int kandydaciA[3] = {indeksA1, indeksA2, indeksA3};
  int kandydaciC[3] = {indeksC1, indeksC2, indeksC3};
  // dla każdej pary skrajnych hoteli A i C z innych sieci, sprawdź każdy hotel B z innej sieci
  // przeiteruj kandydatów A
  for (int i = 0; i < 3; i++) {
    int indeksA = kandydaciA[i];
    int siecA = hotele[indeksA][0];
    // przeiteruj kandydatów C
    for(int j = 0; j < 3; j++) {
      int indeksC = kandydaciC[j];
      int siecC = hotele[indeksC][0];
      // jeżeli hotel A jest innej sieci niż hotel C
      if (indeksA < indeksC && siecA != siecC) {
        // sprawdź wszystkie hotele pomiędzy hotelem A i C - bieżący indeks pętli to kandydat B
        for (int k = indeksA + 1; k < indeksC; k++) {
          int siecB = hotele[k][0];
          // jeżeli kandydat B jest innej sieci niż kandydat A i C
          if (siecB != siecA && siecB != siecC) {
            // sprawdź odległość między nimi - min(B - A, C - B)
            int kilometrazA = hotele[indeksA][1], kilometrazB = hotele[k][1], kilometrazC = hotele[indeksC][1];
            najdalsze3 = maxInt(najdalsze3, minInt(kilometrazB - kilometrazA, kilometrazC - kilometrazB));
          }
        }
      }
    }
  }
  // zwolnij pamięć tablicy z hotelami
  free2DArray(hotele, liczbaHoteli);

  // wypisz wynik
  printf("%d %d", najblizsze3, najdalsze3);

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
int maxInt(int a, int b) {
  return a > b ? a : b;
}

// pomocnicza funkcja -> fmin dla integerów
int minInt(int a, int b) {
  return a < b ? a : b;
}