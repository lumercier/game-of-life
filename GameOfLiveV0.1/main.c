#include <stdio.h>
#include <stdlib.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "grille.h"
#include "sdl_affichage.h"
#include "historique.h"

int main(int argc, char *argv[]) {
   int lignes, colonnes, choix ;
    afficher_menu();


while (1) {
        printf("Choix : ");
        if (scanf("%d", &choix) != 1 || (choix != 1 && choix != 2 && choix != 3)){
            printf("Choix invalide, veuillez réessayer.\n");
            while (getchar() != '\n'); // Vider le buffer d'entrée
        }
        else {
            break;  // Sortir de la boucle si l'entrée est valide
        }
    }
    if (choix == 3) {
        return 0;
    }

    printf("Entrez le nombre de lignes : ");
    scanf("%d", &lignes);
    printf("Entrez le nombre de colonnes : ");
    scanf("%d", &colonnes);



    bool **grille = safe_malloc(lignes * sizeof(bool *));
    bool **grille_suivante = safe_malloc(lignes * sizeof(bool *));
    for (int i = 0; i < lignes; i++) {
        grille[i] = safe_malloc(colonnes * sizeof(bool));
        grille_suivante[i] = safe_malloc(colonnes * sizeof(bool));
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur SDL_Init: %s\n", SDL_GetError());
        return 1;
    }
/*
        if (TTF_Init() == -1) {
        printf("Erreur TTF_Init : %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

      printf("SDL_ttf est correctement intégré.\n");
    TTF_Quit();
    SDL_Quit();

    */


       switch (choix) {
        case 1:
            init_grille_random(grille, lignes, colonnes);
            break;
        case 2:
            charger_grille(grille, lignes, colonnes);
            break;
    }


    SDL_Window *window = SDL_CreateWindow("Jeu de la Vie - SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, colonnes * CELL_SIZE, lignes * CELL_SIZE, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    // Initialisation de la grille et de l'historique
    //init_grille_random(grille, lignes, colonnes);
    Historique *historique = init_historique(lignes, colonnes);
    ajouter_generation(historique, grille);

    int running = 1, paused = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_SPACE) {
                        paused = !paused; // Basculer entre pause et reprise
                    } else if (event.key.keysym.sym == SDLK_s) {
                        sauvegarder_grille(grille, lignes, colonnes);
                        printf("Grille sauvegardée!\n");
                    } else if (event.key.keysym.sym == SDLK_l) {
                        charger_grille(grille, lignes, colonnes);

                        ajouter_generation(historique, grille);
                    } else if (event.key.keysym.sym == SDLK_LEFT) {
                        // Revenir à la génération précédente
                        bool **prev_grille = generation_precedente(historique);
                        if (prev_grille) {
                            grille = prev_grille;
                        }
                    } else if (event.key.keysym.sym == SDLK_RIGHT) {
                        // Avancer à la génération suivante
                        bool **next_grille = generation_suivante(historique);
                        if (next_grille) {
                            grille = next_grille;
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        int x = event.button.x / CELL_SIZE;
                        int y = event.button.y / CELL_SIZE;
                        if (x >= 0 && x < colonnes && y >= 0 && y < lignes) {
                            grille[y][x] = !grille[y][x]; // Inverser l'état de la cellule
                        }
                    }
                    break;
            }
        }

        if (!paused) {
            next_generation(grille, grille_suivante, lignes, colonnes);
            bool **temp = grille;
            grille = grille_suivante;
            grille_suivante = temp;
            ajouter_generation(historique, grille);
        }
        affichage_grille(grille, lignes, colonnes, renderer);
        SDL_Delay(100);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    for (int i = 0; i < lignes; i++) {
        free(grille[i]);
        free(grille_suivante[i]);
    }
    free(grille);
    free(grille_suivante);
    free_historique(historique);

    return 0;
}
