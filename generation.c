#include <stdio.h>
#include <stdlib.h>

int generer_trie(int n, const char *nom_fichier) {
    FILE *f = fopen(nom_fichier, "w");
    if (f == NULL) {
        printf("Erreur : impossible de creer %s\n", nom_fichier);
        return 0;
    }
    fprintf(f, "%d\n", n);          // 1re ligne : la taille n
    for (int i = 0; i < n; i++) {
        fprintf(f, "%d\n", 2 * i);  // une valeur par ligne
    }
    fclose(f);
    return 1;
}

int main(void) {
    int tailles[] = {100000, 200000, 400000, 600000, 800000,
                     1000000, 1200000, 1400000, 1600000, 1800000};
    int nb = sizeof(tailles) / sizeof(tailles[0]);
    char nom[100];

    for (int k = 0; k < nb; k++) {
        sprintf(nom, "data\\trie_%d.txt", tailles[k]);
        generer_trie(tailles[k], nom);
    }
    return 0;
}