#ifndef SDL_AFFICHAGE_H
#define SDL_AFFICHAGE_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define CELL_SIZE 20

// Prototypes des fonctions pour l'affichage avec SDL
void affichage_grille(bool **grille, int lignes, int colonnes, SDL_Renderer *renderer);

#endif

