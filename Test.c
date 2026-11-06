#include <stdio.h>
#include <stdlib.h>

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

int main(void) {
    int n = 100000;
    char nom[100];

    sprintf(nom, "data\\trie_%d.txt", n);
    int *T = lire_fichier(nom, n);
    if (T == NULL) return 1;

    printf("Trie    : T[0]=%d  T[1]=%d  T[n-1]=%d\n", T[0], T[1], T[n - 1]);
    free(T);

    sprintf(nom, "data\\nontrie_%d.txt", n);
    T = lire_fichier(nom, n);
    if (T == NULL) return 1;

    printf("Non trie: T[0]=%d  T[1]=%d  T[n-1]=%d\n", T[0], T[1], T[n - 1]);
    free(T);

    return 0;
}