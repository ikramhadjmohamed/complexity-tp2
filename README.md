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
- Temps : [à compléter à partir de `resultatsB.csv`].

## Conclusion

[À compléter : comparaison théorie et expérience pour les parties A et B.]