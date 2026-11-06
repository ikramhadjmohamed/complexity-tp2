void MaxEtMinB(int T[], int n, int *max, int *min, int *compteur)
{
    int temp;
    *compteur = 0;

    // Etape 1 : comparer les elements par paires
    for (int i = 0; i + 1 < n; i += 2)
    {
        (*compteur)++;

        if (T[i] < T[i + 1])
        {
            temp = T[i];
            T[i] = T[i + 1];
            T[i + 1] = temp;
        }
    }

    // Initialisation avec la premiere paire
    *max = T[0];
    *min = T[1];

    // Etape 2 et 3 : chercher min et max
    for (int i = 2; i + 1 < n; i += 2)
    {
        (*compteur)++;

        if (T[i] > *max)
            *max = T[i];

        (*compteur)++;

        if (T[i + 1] < *min)
            *min = T[i + 1];
    }

    // Si n est impair, le dernier element n'a pas ete compare
    if (n % 2 != 0)
    {
        (*compteur)++;

        if (T[n - 1] > *max)
            *max = T[n - 1];

        (*compteur)++;

        if (T[n - 1] < *min)
            *min = T[n - 1];
    }
}