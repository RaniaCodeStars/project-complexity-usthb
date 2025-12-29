#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

// --- ALGORITHME HEAP SORT (D'après l'énoncé) ---

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

// Procédure pour maintenir la propriété du tas (Entonnoir)
void heapify(int T[], int n, int i)
{
  int largest = i;
  int left = 2 * i + 1;  // Fils gauche
  int right = 2 * i + 2; // Fils droit

  if (left < n && T[left] > T[largest])
    largest = left;

  if (right < n && T[right] > T[largest])
    largest = right;

  if (largest != i)
  {
    swap(&T[i], &T[largest]);
    heapify(T, n, largest);
  }
}

// Fonction de tri principale demandée
void heapSort(int T[], int n)
{
  // 1. Construction du tas (Building the heap)
  for (int i = n / 2 - 1; i >= 0; i--)
  {
    heapify(T, n, i);
  }

  // 2. Extraction du max et tri ascendant
  for (int i = n - 1; i > 0; i--)
  {
    swap(&T[0], &T[i]); // On déplace le max à la fin
    heapify(T, i, 0);   // On rétablit le tas sur le reste
  }
}

// --- PROTOCOLE DE TEST (Moyenne sur 5 essais) [cite: 13] ---

double measureAverageTime(int n, int type)
{
  double totalTime = 0;
  int *testArray = (int *)malloc(n * sizeof(int));

  for (int k = 0; k < 5; k++)
  { // 5 essais par taille [cite: 13]
    for (int j = 0; j < n; j++)
    {
      if (type == 0)
        testArray[j] = j; // Meilleur cas
      else if (type == 1)
        testArray[j] = n - j; // Pire cas
      else
        testArray[j] = rand() % 100000; // Cas aléatoire [cite: 12]
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);
    heapSort(testArray, n);
    gettimeofday(&end, NULL);

    double execTime = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) * 1e-6;
    totalTime += execTime;
  }
  free(testArray);
  return totalTime / 5.0;
}

int main()
{
  // Choix des tailles n pertinentes [cite: 14]
  int sizes[] = {5000, 10000, 20000, 50000, 100000, 1000000, 2000000, 500000, 1000000};
  int numSizes = sizeof(sizes) / sizeof(sizes[0]);
  srand(time(NULL));

  printf("Etude Experimentale du Heap Sort\n");
  printf("------------------------------------------------------------\n");
  printf("Taille(n)\tMeilleur Cas\tPire Cas\tCas Aleatoire\n");
  printf("------------------------------------------------------------\n");

  for (int i = 0; i < numSizes; i++)
  {
    int n = sizes[i];
    double best = measureAverageTime(n, 0);
    double worst = measureAverageTime(n, 1);
    double random = measureAverageTime(n, 2);

    printf("%d\t\t%.6f\t%.6f\t%.6f\n", n, best, worst, random);
  }
  return 0;
}