void MaxEtMinA(int T[], int n, int *max, int *min, int *compteur)
{
    *max = T[0];
    *min = T[0];
    *compteur = 0;

    for (int i = 1; i < n; i++)
    {
        (*compteur)++;

        if (T[i] > *max)
            *max = T[i];

        (*compteur)++;

        if (T[i] < *min)
            *min = T[i];
    }
}