#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Codes_Sources/Recherche_MinMax/B1.c"
#include "Codes_Sources/Recherche_MinMax/B2.c"

int *lire_fichier(const char *nom_fichier, int n) {
    FILE *f = fopen(nom_fichier, "r");
    if (f == NULL) {
        printf("Erreur : impossible d'ouvrir %s\n", nom_fichier);
        return NULL;
    }
    int *T = malloc(n * sizeof(int));
    if (T == NULL) { fclose(f); return NULL; }
    for (int i = 0; i < n; i++) {
        if (fscanf(f, "%d", &T[i]) != 1) {
            printf("Erreur : fichier trop court (ligne %d)\n", i);
            free(T); fclose(f);
            return NULL;
        }
    }
    fclose(f);
    return T;
}

typedef void (*FctMM)(int[], int, int*, int*, int*);

// mode 0 : f sur T | mode 1 : copie puis f sur la copie | mode 2 : copie seule
double mesurer_mm(FctMM f, int T[], int copie[], int n, int mode) {
    int mx, mn, c;
    volatile int sink = 0;
    long reps = 1;
    for (;;) {
        clock_t d = clock();
        for (long r = 0; r < reps; r++) {
            if (mode >= 1) memcpy(copie, T, n * sizeof(int));
            if (mode == 0)      f(T, n, &mx, &mn, &c);
            else if (mode == 1) f(copie, n, &mx, &mn, &c);
            sink += copie[0];   // evite que la copie soit supprimee
        }
        double t = (double)(clock() - d) / CLOCKS_PER_SEC;
        if (t >= 0.05 || reps >= 1000000000L) return t / reps;
        reps *= 10;
    }
}

int main(void) {
    int tailles[] = {100000, 200000, 400000, 600000, 800000,
                     1000000, 1200000, 1400000, 1600000, 1800000,
                     2000000, 4000000, 6000000, 8000000};
    int nb = sizeof(tailles) / sizeof(tailles[0]);
    char nom[100];

    FILE *csv = fopen("Resultats_experimentaux\\resultatsB.csv", "w");
    if (csv == NULL) { printf("Erreur : resultatsB.csv\n"); return 1; }
    fprintf(csv, "n;comp_A;comp_B;temps_A_s;temps_B_s\n");

    for (int k = 0; k < nb; k++) {
        int n = tailles[k];
        sprintf(nom, "data\\nontrie_%d.txt", n);
        int *T = lire_fichier(nom, n);
        int *copie = malloc(n * sizeof(int));
        if (T == NULL || copie == NULL) { fclose(csv); return 1; }

        // 1. comparaisons (un seul appel suffit)
        int mxA, mnA, cA, mxB, mnB, cB;
        memcpy(copie, T, n * sizeof(int));
        MaxEtMinA(T, n, &mxA, &mnA, &cA);
        MaxEtMinB(copie, n, &mxB, &mnB, &cB);
        int ok = (mxA == mxB && mnA == mnB);

        // 2. temps
        double tA      = mesurer_mm(MaxEtMinA, T, copie, n, 0);
        double tBcopie = mesurer_mm(MaxEtMinB, T, copie, n, 1);
        double tcopie  = mesurer_mm(NULL,      T, copie, n, 2);
        double tB = tBcopie - tcopie;

        fprintf(csv, "%d;%d;%d;%.9f;%.9f\n", n, cA, cB, tA, tB);
        printf("n=%d  compA=%d compB=%d  tA=%.6f s  tB=%.6f s  %s\n",
               n, cA, cB, tA, tB, ok ? "" : "<<< INCOHERENT");

        free(T);
        free(copie);
    }
    fclose(csv);
    printf("\nTermine : resultatsB.csv\n");
    return 0;
}