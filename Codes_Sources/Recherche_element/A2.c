int rechElets_TabTries(int T[], int n, int x)
{
    for (int i = 0; i < n; i++)
    {
        if (T[i] == x)
            return 1;

        if (T[i] > x)
            return 0;
    }

    return 0;
}