#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gnomeSort(int A[], int n) {
    int i = 0;
    while (i < n) {
        if (i == 0 || A[i] >= A[i - 1]) { //si on est dans la premiere case du tableau ou pas atteint la fin du tableau
            i++; //si les elements sont ordonnés on incrémente 
        } else {
            int temp = A[i]; //mettre la valeur de la case dans une variable temporaire
            A[i] = A[i - 1]; //permuter les cases
            A[i - 1] = temp; 
            i--; //revenir en arriere pour comparer 
        }
    }
}
/* --------- Génération des tableaux --------- */

void tableauTrie(int A[], int n) {          // Meilleur cas
    for (int i = 0; i < n; i++)
        A[i] = i;
}

void tableauInverse(int A[], int n) {       // Pire cas
    for (int i = 0; i < n; i++)
        A[i] = n - i;
}

void tableauAleatoire(int A[], int n) { //remplir le tableau de valeurs aléatoires Cas Moyen
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100000; //parcourir tout le tableau
    }
}

//test de temps

void testerCas(char *nomCas, void (*init)(int*, int), int n) {
    int *A = (int *)malloc(n * sizeof(int)); //allocation dynamique d'un tableau de n entiers
    double temps; //variable temps pour stocker le temps d'execution 
    clock_t debut, fin; //temps de debut et de fin 

    printf("\n=== Test Gnome Sort pour %s | n = %d ===\n", nomCas, n);

    for (int k = 1; k <= 5; k++) {
        init(A, n); //initialisation du tableau

        debut = clock(); //enregistrer l'instant du début du tri
        gnomeSort(A, n);
        fin = clock(); //enregistrer l'instant du fin du tri

        temps = ((double)(fin - debut)) / CLOCKS_PER_SEC; //convertir le temps CPU en secondes
        printf("Execution %d : %.6f secondes\n", k, temps); //afficher le temps d'execution 
    }

    free(A); //libere la mémoire alloué 
}

int main() {
    srand(time(NULL)); //Initialise le générateur de nombres aléatoires qui evite d'avoir les memes valeurs a chaque execution 

    int tailles[] = {100, 500, 20000};
    int nbTailles = 3;

    for (int i = 0; i < nbTailles; i++) {
        int n = tailles[i];

        testerCas("Meilleur cas (tableau trie)", tableauTrie, n);
        testerCas("Pire cas (tableau inverse)", tableauInverse, n);
        testerCas("Cas moyen (tableau melange)", tableauAleatoire, n);
    }
    return 0;
}
