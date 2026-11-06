void MaxEtMinB(int T[], int n, int *max, int *min, int *comp)
{
    int i, temp;
    *comp = 0;

    for (i = 0; i < n - 1; i += 2)
    {
        (*comp)++;
        if (T[i] > T[i+1])
        {
            temp = T[i];
            T[i] = T[i+1];
            T[i+1] = temp;
        }
    }

    *min = T[0];
    *max = T[1];

    for (i = 2; i < n - 1; i += 2)
    {
        (*comp)++;
        if (T[i] < *min)
            *min = T[i];

        (*comp)++;
        if (T[i+1] > *max)
            *max = T[i+1];
    }

    if (n % 2 != 0)
    {
        (*comp)++;
        if (T[n-1] < *min)
            *min = T[n-1];

        (*comp)++;
        if (T[n-1] > *max)
            *max = T[n-1];
    }
}