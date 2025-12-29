#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

// Fonction key : extrait le i-ème chiffre
int key(int x, int i)
{
  int p = 1;
  for (int j = 0; j < i; j++)
    p *= 10;
  return (x / p) % 10;
}

// Fonction SortAux : Tri stable par comptage pour un chiffre donné
void SortAux(int T[], int n, int i)
{
  int *output = (int *)malloc(n * sizeof(int));
  int count[10] = {0};

  for (int j = 0; j < n; j++)
    count[key(T[j], i)]++;
  for (int j = 1; j < 10; j++)
    count[j] += count[j - 1];

  for (int j = n - 1; j >= 0; j--)
  {
    int k_val = key(T[j], i);
    output[count[k_val] - 1] = T[j];
    count[k_val]--;
  }

  for (int j = 0; j < n; j++)
    T[j] = output[j];
  free(output);
}

void RadixSort(int T[], int n, int k_digits)
{
  for (int i = 0; i < k_digits; i++)
  {
    SortAux(T, n, i);
  }
}

// Protocole de mesure de temps (Moyenne de 5 essais)
double measureRadixTime(int n, int k_digits, int type)
{
  double totalTime = 0;
  int *testArray = (int *)malloc(n * sizeof(int));

  for (int k = 0; k < 5; k++)
  {
    // Remplissage selon le cas
    for (int j = 0; j < n; j++)
    {
      if (type == 0)
        testArray[j] = j; // Meilleur cas (trié)
      else if (type == 1)
        testArray[j] = n - j; // Pire cas (inversé)
      else
        testArray[j] = rand() % 100000; // Aléatoire
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);
    RadixSort(testArray, n, k_digits);
    gettimeofday(&end, NULL);

    totalTime += (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) * 1e-6;
  }

  free(testArray);
  return totalTime / 5.0;
}

int main()
{
  int sizes[] = {5000, 10000, 20000, 50000, 100000, 200000, 500000, 1000000};
  int numSizes = sizeof(sizes) / sizeof(sizes[0]);
  srand(time(NULL));

  printf("Etude du Radix Sort (k=5)\n");
  printf("Taille(n)\tMeilleur(s)\tPire(s)\t\tAleatoire(s)\n");
  printf("------------------------------------------------------------\n");

  for (int i = 0; i < numSizes; i++)
  {
    double t_best = measureRadixTime(sizes[i], 5, 0);
    double t_worst = measureRadixTime(sizes[i], 5, 1);
    double t_rand = measureRadixTime(sizes[i], 5, 2);

    printf("%d\t\t%.6f\t%.6f\t%.6f\n", sizes[i], t_best, t_worst, t_rand);
  }

  return 0;
}