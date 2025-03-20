#include "sdl_affichage.h"
void affichage_grille(bool **grille, int lignes, int colonnes, SDL_Renderer *renderer) {
    // Définir la couleur de fond (noir)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer); // Nettoyer l'écran

    // Parcourir toutes les cellules de la grille
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            // Définir un rectangle correspondant à la cellule
            SDL_Rect cell = {
                j * CELL_SIZE, // Position X (multipliée par la taille d'une cellule)
                i * CELL_SIZE, // Position Y
                CELL_SIZE,     // Largeur
                CELL_SIZE      // Hauteur
            };

            // Définir la couleur en fonction de l'état de la cellule
            if (grille[i][j]) {
                // Cellule vivante : bleu
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            } else {
                // Cellule morte : noir
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }

            // Dessiner la cellule
            SDL_RenderFillRect(renderer, &cell);
        }
    }

    // Afficher les changements
    SDL_RenderPresent(renderer);
}
