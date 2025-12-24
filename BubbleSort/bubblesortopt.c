#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

// Tri à bulles classique [cite: 27]
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

// Tri à bulles optimisé [cite: 44]
void bubbleSortOpt(int *T, int n)
{
  int change, i, m = n - 1;
  do
  {
    change = 0;
    for (i = 0; i < m; i++)
    {
      if (T[i] > T[i + 1])
      {
        int temp = T[i];
        T[i] = T[i + 1];
        T[i + 1] = temp;
        change = 1;
      }
    }
    m--; // Après chaque itération, le plus grand est à sa place [cite: 42, 57]
  } while (change);
}

// Fonction de mesure avec moyenne sur 5 essais
double measureAverageTime(void (*sortFunc)(int *, int), int n, int type)
{
  double totalTime = 0;
  int *testArray = (int *)malloc(n * sizeof(int));

  for (int k = 0; k < 5; k++)
  {
    // Remplissage selon le cas [cite: 12]
    for (int j = 0; j < n; j++)
    {
      if (type == 0)
        testArray[j] = j; // Meilleur cas (trié)
      else if (type == 1)
        testArray[j] = n - j; // Pire cas (inversé)
      else
        testArray[j] = rand() % 10000; // Cas aléatoire [cite: 12]
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);
    sortFunc(testArray, n);
    gettimeofday(&end, NULL);

    double execTime = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) * 1e-6;
    totalTime += execTime;
  }

  free(testArray);
  return totalTime / 5.0; // Retourne la moyenne
}

int main()
{
  // Choix des tailles n pertinentes [cite: 14]
  int sizes[] = {500, 1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000};
  int numSizes = sizeof(sizes) / sizeof(sizes[0]);
  srand(time(NULL));

  printf("Taille(n)\tSort_Best\tSortOpt_Best\tSort_Worst\tSortOpt_Worst\n");
  for (int i = 0; i < numSizes; i++)
  {
    int n = sizes[i];
    double t1 = measureAverageTime(bubbleSort, n, 0);
    double t2 = measureAverageTime(bubbleSortOpt, n, 0);
    double t3 = measureAverageTime(bubbleSort, n, 1);
    double t4 = measureAverageTime(bubbleSortOpt, n, 1);

    printf("%d\t        %.6f\t  %.6f\t   %.6f\t    %.6f\n", n, t1, t2, t3, t4);
  }
  return 0;
}