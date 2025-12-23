#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ---------------- Quick Sort ---------------- */

int partition(int tab[], int d, int f) {
    int pivot = tab[d];
    int i = d + 1;
    int j = f;
    int temp;

    while (1) {
        while (i <= f && tab[i] <= pivot)
            i++;

        while (tab[j] > pivot)
            j--;

        if (i >= j)
            break;

        temp = tab[i];
        tab[i] = tab[j];
        tab[j] = temp;
    }

    tab[d] = tab[j];
    tab[j] = pivot;

    return j;
}

void quickSort(int tab[], int p, int r) {
    if (p < r) {
        int q = partition(tab, p, r);
        quickSort(tab, p, q - 1);
        quickSort(tab, q + 1, r);
    }
}

/* ---------------- Initialisation des tableaux ---------------- */

void tableauTrie(int A[], int n) {          // Pire cas
    for (int i = 0; i < n; i++)
        A[i] = i;
}

void tableauInverse(int A[], int n) {       // Pire cas aussi
    for (int i = 0; i < n; i++)
        A[i] = n - i;
}

void tableauAleatoire(int A[], int n) {     // Cas moyen
    for (int i = 0; i < n; i++)
        A[i] = rand() % 100000;
}

/* ---------------- Mesure du temps ---------------- */

void testerCas(char *nomCas, void (*init)(int*, int), int n) {
    int *A = (int *)malloc(n * sizeof(int));
    clock_t debut, fin;
    double temps;

    printf("\n--- %s | n = %d ---\n", nomCas, n);

    for (int k = 1; k <= 5; k++) {
        init(A, n);

        debut = clock();
        quickSort(A, 0, n - 1);
        fin = clock();

        temps = (double)(fin - debut) / CLOCKS_PER_SEC;
        printf("Execution %d : %.6f secondes\n", k, temps);
    }

    free(A);
}

int main() {
    srand(time(NULL));

    int tailles[] = {100, 500, 20000};

    for (int i = 0; i < 3; i++) {
        int n = tailles[i];

        testerCas("Meilleur cas (quasi equilibre)", tableauAleatoire, n);
        testerCas("Pire cas (tableau trie)", tableauTrie, n);
        testerCas("Cas moyen (tableau melange)", tableauAleatoire, n);
    }

    return 0;
}
