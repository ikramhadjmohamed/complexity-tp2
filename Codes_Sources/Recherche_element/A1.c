int rechElets_TabNonTries(int T[], int n, int x)
{
    for (int i = 0; i < n; i++)
    {
        if (T[i] == x)
            return 1;
    }

    return 0;
}