#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>


void bubbleSort(int *T, int n)
{
  int change, i;
  do
  {
    change = 0;
    for (i = 0; i < n - 1; i++)
    {
      if (T[i] > T[i + 1])
      {
        int temp = T[i];
        T[i] = T[i + 1];
        T[i + 1] = temp;
        change = 1;
      }
    }
  } while (change);
}

// Bubble Sort optimisé
void bubbleSortOpt(int *T, int n)
{
  int change, i, m = n - 1;
  do
  {
    change = 0;
    for (i = 0; i < m; i++)
    { // on s'arrête à m
      if (T[i] > T[i + 1])
      {
        int temp = T[i];
        T[i] = T[i + 1];
        T[i + 1] = temp;
        change = 1;
      }
    }
    m--; // réduire la zone non triée
  } while (change);
}

// Fonction pour mesurer le temps en secondes
double measureTime(void (*sortFunc)(int *, int), int *T, int n)
{
  struct timeval start, end;
  gettimeofday(&start, NULL);
  sortFunc(T, n);
  gettimeofday(&end, NULL);
  long seconds = end.tv_sec - start.tv_sec;
  long microseconds = end.tv_usec - start.tv_usec;
  return seconds + microseconds * 1e-6;
}

// Fonction pour copier un tableau
void copyArray(int *src, int *dest, int n)
{
  for (int i = 0; i < n; i++)
    dest[i] = src[i];
}

int main()
{
  int sizes[] = {100, 500, 1000, 2000, 5000, 10000, 20000};
  int numSizes = sizeof(sizes) / sizeof(sizes[0]);
  int i, j;

  srand(time(0));

  for (i = 0; i < numSizes; i++)
  {
    int n = sizes[i];
    int *original = (int *)malloc(n * sizeof(int));
    int *T = (int *)malloc(n * sizeof(int));

    printf("\n=== Taille du tableau: %d ===\n", n);

    // Meilleur cas: tableau déjà trié
    for (j = 0; j < n; j++)
      original[j] = j;

    copyArray(original, T, n);
    printf("BubbleSort meilleur cas: %.6f s\n", measureTime(bubbleSort, T, n));

    copyArray(original, T, n);
    printf("BubbleSortOpt meilleur cas: %.6f s\n", measureTime(bubbleSortOpt, T, n));

    // Pire cas: tableau inversé
    for (j = 0; j < n; j++)
      original[j] = n - j;

    copyArray(original, T, n);
    printf("BubbleSort pire cas: %.6f s\n", measureTime(bubbleSort, T, n));

    copyArray(original, T, n);
    printf("BubbleSortOpt pire cas: %.6f s\n", measureTime(bubbleSortOpt, T, n));

    free(original);
    free(T);
  }

  return 0;
}
