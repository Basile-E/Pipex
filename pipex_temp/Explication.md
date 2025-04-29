# Explication du programme Pipex

## Introduction
Le programme **Pipex** est conçu pour reproduire le comportement d'une commande shell qui redirige les entrées et sorties standard à l'aide de pipes. Il permet d'exécuter des commandes en chaîne, en redirigeant les sorties d'une commande comme entrées pour une autre. Ce document explique le déroulement du programme, les fonctions principales et les concepts utilisés.

---

## Fonctionnement général
Le programme prend en entrée quatre arguments :
1. `infile` : fichier d'entrée.
2. `cmd1` : première commande à exécuter.
3. `cmd2` : deuxième commande à exécuter.
4. `outfile` : fichier de sortie.

Le programme exécute l'équivalent de la commande shell suivante :
```bash
< infile cmd1 | cmd2 > outfile
```

---

## Explication des fonctions principales

### `main`
La fonction principale :
1. Vérifie que le nombre d'arguments est correct.
2. Crée un pipe avec `pipe(fd)`.
3. Crée un processus enfant avec `fork()`.
   - Si le processus est l'enfant (`pid1 == 0`), il exécute `child_process`.
   - Le processus parent attend la fin de l'enfant avec `waitpid` et exécute `parent_process`.

### `child_process`
Cette fonction :
1. Ouvre le fichier d'entrée (`infile`) en lecture avec `open`.
2. Redirige la sortie standard vers l'extrémité d'écriture du pipe avec `dup2`.
3. Redirige l'entrée standard vers le fichier d'entrée avec `dup2`.
4. Ferme l'extrémité de lecture du pipe.
5. Exécute la commande `cmd1` avec `execve`.

### `parent_process`
Cette fonction :
1. Ouvre le fichier de sortie (`outfile`) en écriture avec `open`.
2. Redirige l'entrée standard vers l'extrémité de lecture du pipe avec `dup2`.
3. Redirige la sortie standard vers le fichier de sortie avec `dup2`.
4. Ferme l'extrémité d'écriture du pipe.
5. Exécute la commande `cmd2` avec `execve`.

### `find_path`
Cette fonction :
1. Recherche la variable d'environnement `PATH`.
2. Divise les chemins possibles en utilisant `ft_split`.
3. Construit le chemin complet pour la commande et vérifie son existence avec `access`.
4. Retourne le chemin valide ou `NULL` si aucun chemin n'est trouvé.

### `execute`
Cette fonction :
1. Divise la commande en arguments avec `ft_split`.
2. Trouve le chemin de la commande avec `find_path`.
3. Exécute la commande avec `execve`.
4. Affiche une erreur si l'exécution échoue.

### `error`
Affiche un message d'erreur avec `perror` et termine le programme avec `exit`.

---

## Concepts clés

### `fork`
`fork` crée un nouveau processus. Le processus parent reçoit l'ID du processus enfant, tandis que l'enfant reçoit `0`.

### `pipe`
`pipe` crée un canal de communication entre deux processus. Il génère deux descripteurs de fichiers :
- `fd[0]` : lecture.
- `fd[1]` : écriture.

### `dup2`
`dup2` redirige un descripteur de fichier vers un autre. Par exemple, il peut rediriger la sortie standard vers un fichier ou un pipe.

### `execve`
`execve` remplace le processus courant par un nouveau programme. Il prend en entrée le chemin du programme, ses arguments et ses variables d'environnement.

---

## Conclusion
Le programme **Pipex** utilise des concepts avancés de gestion des processus et des descripteurs de fichiers pour reproduire le comportement des pipes en shell. Chaque fonction joue un rôle spécifique pour assurer la redirection correcte des entrées et sorties entre les commandes.