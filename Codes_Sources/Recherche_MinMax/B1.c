void MaxEtMinA(int T[], int n, int *max, int *min, int *comp)
{
    int i;

    *max = T[0];
    *min = T[0];
    *comp = 0;

    for (i = 1; i < n; i++)
    {
        (*comp)++;
        if (T[i] > *max)
            *max = T[i];

        (*comp)++;
        if (T[i] < *min)
            *min = T[i];
    }
}