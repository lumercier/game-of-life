#ifndef GRILLE_H
#define GRILLE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Prototypes des fonctions pour la gestion de la grille
void init_grille(bool **grille, int lignes, int colonnes);
void init_grille_random(bool **grille, int lignes, int colonnes);
int compte_voisins(bool **grille, int x, int y, int lignes, int colonnes);
void next_generation(bool **current, bool **next, int lignes, int colonnes);
//void sauvegarder_grille(bool **grille, int lignes, int colonnes, const char *nom_fichier);
void sauvegarder_grille(bool **grille, int lignes, int colonnes);
void charger_grille(bool **grille, int lignes, int colonnes);
void *safe_malloc(size_t size);
void afficher_menu() ;

#endif

