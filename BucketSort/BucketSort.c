#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ---------- Structure liste chaînée ---------- */

typedef struct Node {
    float value;
    struct Node *next;
} Node;

/* ---------- Insertion triée ---------- */

void insertionSorted(Node **head, float value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;

    if (*head == NULL || (*head)->value >= value) {
        newNode->next = *head;
        *head = newNode;
    } else {
        Node *current = *head;
        while (current->next != NULL && current->next->value < value)
            current = current->next;

        newNode->next = current->next;
        current->next = newNode;
    }
}

/* ---------- Bucket Sort ---------- */

void bucketSort(float A[], int n) {
    Node **B = (Node **)malloc(n * sizeof(Node*));

    for (int i = 0; i < n; i++)
        B[i] = NULL;

    for (int i = 0; i < n; i++) {
        int index = (int)(n * A[i]);
        insertionSorted(&B[index], A[i]);
    }

    int k = 0;
    for (int i = 0; i < n; i++) {
        Node *current = B[i];
        while (current != NULL) {
            A[k++] = current->value;
            Node *tmp = current;
            current = current->next;
            free(tmp);
        }
    }

    free(B);
}

/* ---------- Initialisation des cas ---------- */

// Meilleur cas : distribution uniforme
void meilleurCas(float A[], int n) {
    for (int i = 0; i < n; i++)
        A[i] = (float)i / n;
}

// Cas moyen : aléatoire uniforme
void casMoyen(float A[], int n) {
    for (int i = 0; i < n; i++)
        A[i] = (float)rand() / RAND_MAX;
}

// Pire cas : toutes les valeurs dans le même bucket
void pireCas(float A[], int n) {
    for (int i = 0; i < n; i++)
        A[i] = 0.5;
}

/* ---------- Mesure du temps ---------- */

void testerCas(char *nomCas, void (*init)(float*, int), int n) {
    float *A = (float *)malloc(n * sizeof(float));
    clock_t debut, fin;
    double temps, somme = 0.0;

    printf("\n=== %s | n = %d ===\n", nomCas, n);

    for (int k = 1; k <= 5; k++) {
        init(A, n);

        debut = clock();
        bucketSort(A, n);
        fin = clock();

        temps = (double)(fin - debut) / CLOCKS_PER_SEC;
        printf("Execution %d : %.6f secondes\n", k, temps);

        somme += temps;
    }

    printf("Temps moyen : %.6f secondes\n", somme / 5.0);
    free(A);
}

/* ---------- Main ---------- */

int main() {
    srand(time(NULL));

    int tailles[] = {500, 5000, 20000, 50000, 100000, 500000};
    int nb = 6;

    for (int i = 0; i < nb; i++) {
        int n = tailles[i];

        testerCas("Meilleur cas (distribution uniforme)", meilleurCas, n);
        testerCas("Cas moyen (aleatoire)", casMoyen, n);
        testerCas("Pire cas (un seul bucket)", pireCas, n);
    }

    return 0;
}
