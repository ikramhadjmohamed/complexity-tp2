#include <stdio.h>
#include <stdlib.h>

int generer_trie(int n, const char *nom_fichier) {
    FILE *f = fopen(nom_fichier, "w");
    if (f == NULL) {
        printf("Erreur : impossible de creer %s\n", nom_fichier);
        return 0;
    }
    for (int i = 0; i < n; i++) {
        fprintf(f, "%d\n", 2 * i);
    }
    fclose(f);
    return 1;
}

int generer_nontrie(int n, const char *nom_fichier) {
    int *T = malloc(n * sizeof(int));
    if (T == NULL) {
        printf("Erreur : memoire insuffisante\n");
        return 0;
    }
    for (int i = 0; i < n; i++) {
        T[i] = 2 * i;                  // valeurs distinctes
    }
    for (int i = n - 1; i > 0; i--) {  // melange Fisher-Yates
        int j = ((rand() << 15) | rand()) % (i + 1);
        int tmp = T[i];
        T[i] = T[j];
        T[j] = tmp;
    }
    FILE *f = fopen(nom_fichier, "w");
    if (f == NULL) {
        printf("Erreur : impossible de creer %s\n", nom_fichier);
        free(T);
        return 0;
    }
    for (int i = 0; i < n; i++) {
        fprintf(f, "%d\n", T[i]);
    }
    fclose(f);
    free(T);
    return 1;
}

int main(void) {
    int tailles[] = {100000, 200000, 400000, 600000, 800000,
                     1000000, 1200000, 1400000, 1600000, 1800000};
    int nb = sizeof(tailles) / sizeof(tailles[0]);
    char nom[100];

    srand(42);  // graine fixe : memes donnees a chaque execution

    for (int k = 0; k < nb; k++) {
        sprintf(nom, "data\\trie_%d.txt", tailles[k]);
        generer_trie(tailles[k], nom);

        sprintf(nom, "data\\nontrie_%d.txt", tailles[k]);
        generer_nontrie(tailles[k], nom);

        printf("n = %d : OK\n", tailles[k]);
    }
    return 0;
}