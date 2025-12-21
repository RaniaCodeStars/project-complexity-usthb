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

// Fonction pour mesurer le temps en secondes
double measureTime(int *T, int n)
{
  struct timeval start, end;
  gettimeofday(&start, NULL);
  bubbleSort(T, n);
  gettimeofday(&end, NULL);
  long seconds = end.tv_sec - start.tv_sec;
  long microseconds = end.tv_usec - start.tv_usec;
  return seconds + microseconds * 1e-6;
}

int main()
{
  int sizes[] = {100, 500, 1000, 2000, 5000, 10000, 20000};
  int numSizes = sizeof(sizes) / sizeof(sizes[0]);
  int i, j, k;

  srand(time(0));

  for (i = 0; i < numSizes; i++)
  {
    for (k = 1; k < 6; k++)
    {
      printf("\n============================================= Essai %d: =============================================\n", k);

      int n = sizes[i];
      int *T = (int *)malloc(n * sizeof(int));
      printf("\n                          ============ Taille du tableau: %d ============\n", n);

      // 1️⃣ Tableau aléatoire (cas moyen)
      for (j = 0; j < n; j++)
        T[j] = rand() % 10000;
      printf("Temps tableau aleatoire: %.6f s\n", measureTime(T, n));

      // 2️⃣ Tableau déjà trié (meilleur cas)
      for (j = 0; j < n; j++)
        T[j] = j;
      printf("Temps tableau deja trie: %.6f s\n", measureTime(T, n));

      // 3️⃣ Tableau inversé (pire cas)
      for (j = 0; j < n; j++)
        T[j] = n - j;
      printf("Temps tableau inverse: %.6f s\n", measureTime(T, n));

      free(T);
    }
  }

  return 0;
}
