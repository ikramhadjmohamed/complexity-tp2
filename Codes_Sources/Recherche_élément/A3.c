int rechElets_Dicho(int T[], int n, int x)
{
    int debut = 0;
    int fin = n - 1;
    int milieu;

    while (debut <= fin)
    {
        milieu = (debut + fin) / 2;

        if (T[milieu] == x)
            return 1;

        if (x < T[milieu])
            fin = milieu - 1;
        else
            debut = milieu + 1;
    }

    return 0;
}