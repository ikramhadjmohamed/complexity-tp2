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

void ligne(FILE *csv, int n, const char *fct, const char *cas, double t) {
    fprintf(csv, "%d;%s;%s;%.9f\n", n, fct, cas, t);
    printf("n=%d  %s  %s : %.9f s\n", n, fct, cas, t);
}

int main(void) {
    int tailles[] = {100000, 200000, 400000, 600000, 800000,
                     1000000, 1200000, 1400000, 1600000, 1800000};
    int nb = sizeof(tailles) / sizeof(tailles[0]);
    char nom[100];

    FILE *csv = fopen("Resultats_experimentaux\\resultats.csv", "w");
    if (csv == NULL) {
        printf("Erreur : impossible de creer resultats.csv\n");
        return 1;
    }
    fprintf(csv, "n;fonction;cas;temps_s\n");

    for (int k = 0; k < nb; k++) {
        int n = tailles[k];

        sprintf(nom, "data\\nontrie_%d.txt", n);
        int *NT = lire_fichier(nom, n);
        sprintf(nom, "data\\trie_%d.txt", n);
        int *TR = lire_fichier(nom, n);
        if (NT == NULL || TR == NULL) { fclose(csv); return 1; }

        // Non trie
        ligne(csv, n, "NonTrie", "meilleur",     mesurer(rechElets_TabNonTries, NT, n, NT[0],     10000000L));
        ligne(csv, n, "NonTrie", "pire_absent",  mesurer(rechElets_TabNonTries, NT, n, -1,        200L));
        ligne(csv, n, "NonTrie", "pire_dernier", mesurer(rechElets_TabNonTries, NT, n, NT[n - 1], 200L));

        // Trie sequentiel
        ligne(csv, n, "TrieSeq", "meilleur",     mesurer(rechElets_TabTries, TR, n, TR[0],     10000000L));
        ligne(csv, n, "TrieSeq", "pire_absent",  mesurer(rechElets_TabTries, TR, n, 2 * n,     200L));
        ligne(csv, n, "TrieSeq", "pire_dernier", mesurer(rechElets_TabTries, TR, n, TR[n - 1], 200L));

        // Dichotomie
        ligne(csv, n, "Dicho", "meilleur",     mesurer(rechElets_Dicho, TR, n, TR[(n - 1) / 2], 5000000L));
        ligne(csv, n, "Dicho", "pire_absent",  mesurer(rechElets_Dicho, TR, n, -1,              5000000L));
        ligne(csv, n, "Dicho", "pire_dernier", mesurer(rechElets_Dicho, TR, n, TR[0],           5000000L));

        free(NT);
        free(TR);
    }

    fclose(csv);
    printf("\nTermine : Resultats_experimentaux\\resultats.csv\n");
    return 0;
}