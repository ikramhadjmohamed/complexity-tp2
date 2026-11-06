#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Codes_Sources/Recherche_element/A1.c"
#include "Codes_Sources/Recherche_element/A2.c"
#include "Codes_Sources/Recherche_element/A3.c"

// Lit n valeurs dans le fichier et renvoie le tableau (NULL si erreur)
int *lire_fichier(const char *nom_fichier, int n) {
    FILE *f = fopen(nom_fichier, "r");
    if (f == NULL) {
        printf("Erreur : impossible d'ouvrir %s\n", nom_fichier);
        return NULL;
    }
    int *T = malloc(n * sizeof(int));
    if (T == NULL) {
        printf("Erreur : memoire insuffisante\n");
        fclose(f);
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        if (fscanf(f, "%d", &T[i]) != 1) {
            printf("Erreur : fichier trop court (ligne %d)\n", i);
            free(T);
            fclose(f);
            return NULL;
        }
    }
    fclose(f);
    return T;
}

// Temps moyen d'UNE recherche
typedef int (*FctRech)(int[], int, int);

double mesurer(FctRech f, int T[], int n, int x, long reps) {
    volatile int resultat;
    clock_t debut = clock();
    for (long k = 0; k < reps; k++) {
        resultat = f(T, n, x);
    }
    clock_t fin = clock();
    return (double)(fin - debut) / CLOCKS_PER_SEC / reps;
}

int main(void) {
    int n = 100000;
    char nom[100];

    sprintf(nom, "data\\nontrie_%d.txt", n);
    int *NT = lire_fichier(nom, n);
    sprintf(nom, "data\\trie_%d.txt", n);
    int *TR = lire_fichier(nom, n);
    if (NT == NULL || TR == NULL) return 1;

    printf("n = %d\n\n", n);

    printf("--- Non trie ---\n");
    printf("Meilleur (x=T[0])       : %.9f s\n", mesurer(rechElets_TabNonTries, NT, n, NT[0],     10000000L));
    printf("Pire (x absent)         : %.9f s\n", mesurer(rechElets_TabNonTries, NT, n, -1,        1000L));
    printf("Pire (x=T[n-1])         : %.9f s\n", mesurer(rechElets_TabNonTries, NT, n, NT[n - 1], 1000L));

    printf("\n--- Trie, sequentiel ---\n");
    printf("Meilleur (x=T[0])       : %.9f s\n", mesurer(rechElets_TabTries, TR, n, TR[0],     10000000L));
    printf("Pire (x absent > max)   : %.9f s\n", mesurer(rechElets_TabTries, TR, n, 2 * n,     1000L));
    printf("Pire (x=T[n-1])         : %.9f s\n", mesurer(rechElets_TabTries, TR, n, TR[n - 1], 1000L));

    printf("\n--- Dichotomie ---\n");
    printf("Meilleur (x au milieu)  : %.9f s\n", mesurer(rechElets_Dicho, TR, n, TR[(n - 1) / 2], 10000000L));
    printf("Pire (x absent)         : %.9f s\n", mesurer(rechElets_Dicho, TR, n, -1,              10000000L));
    printf("Pire (x=T[0], dernier decoupage) : %.9f s\n", mesurer(rechElets_Dicho, TR, n, TR[0],  10000000L));

    free(NT);
    free(TR);
    return 0;
}