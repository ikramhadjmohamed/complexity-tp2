# TP2 : Recherche d'éléments, maximum et minimum

## Objectif

Étudier expérimentalement la complexité de :

- **Partie A** : trois algorithmes de recherche d'une valeur x dans un tableau de n entiers
  (non trié, trié séquentiel, dichotomie), en meilleur et en pire cas.
- **Partie B** : deux algorithmes de recherche simultanée du maximum et du minimum
  (`MaxEtMinA` naïf, `MaxEtMinB` par paires), en nombre de comparaisons et en temps.

Les mesures sont comparées à la complexité théorique.

## Structure du dépôt

```
TP2
  Codes_Sources
    Recherche_element
      A1.c            rechElets_TabNonTries (recherche séquentielle, tableau non trié)
      A2.c            rechElets_TabTries    (recherche séquentielle, tableau trié)
      A3.c            rechElets_Dicho       (recherche dichotomique)
    Recherche_MinMax
      B1.c            MaxEtMinA (approche naïve)
      B2.c            MaxEtMinB (comparaison par paires)
  data                jeux de données (fichiers texte)
  Resultats_experimentaux
    resultats.csv     résultats de la partie A
    resultatsB.csv    résultats de la partie B
  generation.c        génération des jeux de données
  Test.c              tests et mesures de la partie A
  TestB.c             tests et mesures de la partie B
```

## Compilation et exécution

Toutes les commandes se lancent depuis le dossier `TP2` (Windows, CMD), car les
chemins `data\...` et `Resultats_experimentaux\...` sont relatifs à ce dossier.

```
mkdir data
gcc generation.c -o generation.exe
generation.exe

gcc Test.c -o test.exe
test.exe

gcc TestB.c -o testB.exe
testB.exe
```

L'ordre est important : la génération des données se fait une seule fois, avant les tests.

## Jeux de données

Fichiers dans `data\`, une valeur par ligne, exactement n valeurs (pas d'en-tête).

| Fichier | Contenu | Utilisé par |
|---|---|---|
| `trie_n.txt` | `0, 2, 4, ..., 2(n-1)` (trié, sans doublon) | recherche triée, dichotomie |
| `nontrie_n.txt` | les mêmes valeurs mélangées (Fisher-Yates, `srand(42)`) | recherche non triée, partie B |

- Tailles de la partie A : 100000, 200000, 400000, 600000, 800000, 1000000, 1200000,
  1400000, 1600000, 1800000.
- Tailles de la partie B : les précédentes, plus 2000000, 4000000, 6000000, 8000000
  (fichiers non triés uniquement).
- Les valeurs sont toutes distinctes. La graine fixe permet de régénérer exactement les
  mêmes fichiers.
- La complexité étudiée dépend de n (le nombre d'éléments) et non des valeurs. Les
  tableaux trié et non trié sont deux fichiers distincts, avec des ordres différents.

## Méthode de mesure

- Les fichiers sont lus **avant** le chronométrage : seul l'appel de la fonction est mesuré.
- Le temps est mesuré avec `clock()` (`time.h`). Une seule exécution étant trop courte,
  la fonction est répétée plusieurs fois et le temps total est divisé par le nombre de
  répétitions. Le nombre de répétitions augmente automatiquement (par palier de 10)
  jusqu'à ce que la mesure dure au moins 50 ms.
- `MaxEtMinB` modifie le tableau (échanges de paires). Il est donc appliqué à une copie du
  tableau, et le temps de la copie seule est retranché du résultat.

## Cas testés (partie A)

| Fonction | Meilleur cas | Pire cas (variante 1) | Pire cas (variante 2) |
|---|---|---|---|
| Non trié | x = `T[0]` | x absent (-1) | x = `T[n-1]` |
| Trié séquentiel | x = `T[0]` | x absent, supérieur au max (`2n`) | x = `T[n-1]` |
| Dichotomie | x au milieu | x absent (-1) | x = `T[0]` |

Pour la dichotomie, la variante 2 est l'élément trouvé au dernier découpage.

## Complexité théorique

On compte le nombre de comparaisons entre éléments, en fonction de n.

### Partie A : recherche d'un élément

| Fonction | Meilleur cas | Pire cas |
|---|---|---|
| Non trié | 1 comparaison (x = `T[0]`), O(1) | n comparaisons (x absent ou dernier), O(n) |
| Trié séquentiel | 1 comparaison (x = `T[0]`), O(1) | n tours de boucle (x absent et supérieur au max, ou dernier), O(n) |
| Dichotomie | 1 comparaison (x au milieu), O(1) | environ log2(n) étapes, O(log n) |

**Dichotomie, pire cas.** À chaque étape, la zone de recherche est divisée par 2 :
n, n/2, n/4, ..., 1. Le nombre d'étapes k est le plus petit entier tel que n / 2^k < 1,
c'est-à-dire k = partie entière de log2(n) + 1.

- n = 100 000 : environ 17 étapes
- n = 1 800 000 : environ 21 étapes

### Partie B : maximum et minimum

**MaxEtMinA (naïf).** On initialise max et min avec `T[0]`, puis, pour chacun des
n-1 éléments restants, on fait 2 comparaisons (une avec le max, une avec le min) :

    comparaisons = 2(n - 1)

Le résultat est le même quelles que soient les valeurs (pas de meilleur ni de pire cas).

**MaxEtMinB (par paires), n pair.**

1. On compare les éléments deux à deux : n/2 comparaisons.
2. Le minimum se cherche parmi les n/2 petits : n/2 - 1 comparaisons.
3. Le maximum se cherche parmi les n/2 grands : n/2 - 1 comparaisons.

        comparaisons = n/2 + 2(n/2 - 1) = 3n/2 - 2

Pour n impair, le dernier élément est comparé au min et au max (2 comparaisons de plus)
et on obtient 3(n-1)/2.

| n | MaxEtMinA : 2(n-1) | MaxEtMinB : 3n/2 - 2 |
|---|---|---|
| 100 000 | 199 998 | 149 998 |
| 8 000 000 | 15 999 998 | 11 999 998 |

Le rapport B / A tend vers 3/4 : MaxEtMinB fait environ 25 % de comparaisons en moins.
Les deux algorithmes restent en O(n).

## Vérification expérimentale

Les valeurs de comparaisons mesurées (`comp_A`, `comp_B`) sont **identiques** aux formules
ci-dessus pour les 14 tailles : le compteur confirme le calcul théorique.

Pour les temps, le calcul « temps par élément » (temps / n) permet de vérifier la linéarité :
si ce rapport reste à peu près constant quand n augmente, la complexité est bien O(n).
Par exemple, pour la recherche séquentielle en pire cas, 250 µs pour 100 000 éléments
donnent environ 2,5 ns par comparaison.

## Résultats

### Partie A : `Resultats_experimentaux\resultats.csv`

Colonnes : `n;fonction;cas;temps_s` (une ligne par mesure, 90 lignes).
`fonction` vaut `NonTrie`, `TrieSeq` ou `Dicho`. `cas` vaut `meilleur`, `pire_absent`
ou `pire_dernier`. Le temps est celui d'**une** recherche, en secondes.

### Partie B : `Resultats_experimentaux\resultatsB.csv`

Colonnes : `n;comp_A;comp_B;temps_A_s;temps_B_s` (une ligne par taille, 14 lignes).

## Observations

**Partie A**

- Séquentiel (trié et non trié), pire cas : le temps est proportionnel à n. Quand n passe de
  100000 à 1800000 (facteur 18), le temps est multiplié par environ 19 à 21. Complexité O(n).
- Dichotomie, pire cas : le temps reste de l'ordre de quelques dizaines de nanosecondes
  (39 ns à n = 100000, 76 ns à n = 1800000). Complexité O(log n).
- Meilleur cas : temps constant (quelques nanosecondes), O(1).
- Les deux variantes du pire cas donnent des temps très proches.

**Partie B**

- `MaxEtMinA` fait 2(n-1) comparaisons et `MaxEtMinB` environ 3n/2 - 2 (par exemple
  199998 et 149998 pour n = 100000), soit environ 25 % de comparaisons en moins.
- Temps : les deux courbes sont des droites, donc les deux algorithmes sont en O(n).
  MaxEtMinB est cependant plus lent que MaxEtMinA (environ 41 ms contre 23 ms pour
  n = 8 000 000, valeurs lues sur le graphe), bien qu'il fasse moins de comparaisons.
  [Vérifier ces valeurs dans `resultatsB.csv`.]
- Explication possible (non vérifiée) : MaxEtMinB effectue des échanges et des écritures
  dans le tableau, et son test `T[i] > T[i+1]` est imprévisible sur des données
  aléatoires, ce qui ralentit le processeur. Dans MaxEtMinA, le test `T[i] > max` est
  presque toujours faux, donc plus facile à prédire.

## Conclusion

## Conclusion

- **Partie A.** Les mesures confirment la théorie : la recherche séquentielle est en O(n)
  (le temps est multiplié par environ 19 à 21 quand n est multiplié par 18), la dichotomie
  en O(log n) est plusieurs milliers de fois plus rapide, mais elle exige un tableau trié.
  Le meilleur cas est constant (O(1)) pour les trois fonctions.
- **Partie B.** MaxEtMinB réduit le nombre de comparaisons de 2n à 3n/2, mais cela ne se
  traduit pas par un gain de temps sur notre machine : le nombre de comparaisons ne suffit
  pas à prédire le temps réel. Les deux algorithmes ont la même complexité asymptotique, O(n).
- **Remarque générale.** Dans ce TP, la complexité dépend de n (le nombre d'éléments) et
  non des valeurs, contrairement au TP1 où elle dépendait de la valeur de N.