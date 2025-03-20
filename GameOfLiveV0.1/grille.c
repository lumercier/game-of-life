
#include "grille.h"
#include <stdlib.h>
#include <stdio.h>


void afficher_menu() {

    printf("\n\n\n");
    printf("      **   ********   **     **       *******     ********       **             **         **      **   **   ********\n");
    printf("     /**  /**/////   /**    /**      /**////**   /**/////       /**            ****       /**     /**  /**  /**/////\n");
    printf("     /**  /**        /**    /**      /**    /**  /**            /**           **//**      /**     /**  /**  /**\n");
    printf("     /**  /*******   /**    /**      /**    /**  /*******       /**          **  //**     //**    **   /**  /*******\n");
    printf("     /**  /**////    /**    /**      /**    /**  /**////        /**         **********     //**  **    /**  /**////\n");
    printf(" **  /**  /**        /**    /**      /**    **   /**            /**        /**//////**      //****     /**  /**\n");
    printf("//*****   /********  //*******       /*******    /********      /********  /**     /**       //**      /**  /********\n");
    printf(" /////    ////////    ///////        ///////     ////////       ////////   //      //         //       //   ////////\n");
    printf("\n\n\n");

    printf("1 - Générer une une grille aléatoire\n");
    printf("2 - Charger une grille depuis un fichier\n");
    printf("3 - Quitter\n\n");
}





void init_grille(bool **grille, int lignes, int colonnes) {
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            grille[i][j] = false;
        }
    }

}

void init_grille_random(bool **grille, int lignes, int colonnes) {
    srand(time(NULL));
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            grille[i][j] = rand() % 2;
        }
    }
}

int compte_voisins(bool **grille, int x, int y, int lignes, int colonnes) {
    int count = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < lignes && ny >= 0 && ny < colonnes) {
                count += grille[nx][ny];
            }
        }
    }
    return count;
}

void next_generation(bool **current, bool **next, int lignes, int colonnes) {
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            int neighbors = compte_voisins(current, i, j, lignes, colonnes);
            next[i][j] = (current[i][j]) ? (neighbors == 2 || neighbors == 3) : (neighbors == 3);
        }
    }
}
/*
void sauvegarder_grille(bool **grille, int lignes, int colonnes, const char *nom_fichier) {
    FILE *file = fopen(nom_fichier, "w");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return;
    }
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            fprintf(file, "%d ", grille[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}
*/
void sauvegarder_grille(bool **grille, int lignes, int colonnes) {
    char nom_fichier[100]; // Tableau pour stocker le nom du fichier

    // Demander à l'utilisateur de saisir un nom de fichier
    printf("Entrez le nom du fichier de sauvegarde (sans extension) : ");
    scanf("%s", nom_fichier);

    // Ajouter l'extension .txt au fichier
    strcat(nom_fichier, ".txt");

    // Ouvrir le fichier en mode écriture
    FILE *fichier = fopen(nom_fichier, "w");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    // Sauvegarder la grille ligne par ligne
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            fprintf(fichier, "%d ", grille[i][j]); // Écrire l'état de la cellule (0 ou 1)
        }
        fprintf(fichier, "\n"); // Saut de ligne après chaque ligne de la grille
    }

    fclose(fichier); // Fermer le fichier
    printf("Grille sauvegardée dans '%s'.\n", nom_fichier);
}
void charger_grille(bool **grille, int lignes, int colonnes) {
    char nom_fichier[100]; // Tableau pour stocker le nom du fichier

    // Demander à l'utilisateur de saisir un nom de fichier
    printf("Entrez le nom du fichier à charger (sans extension) : ");
    scanf("%s", nom_fichier);

    // Ajouter l'extension .txt
    strcat(nom_fichier, ".txt");

    // Ouvrir le fichier en mode lecture
    FILE *file = fopen(nom_fichier, "r");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return;
    }

    // Lecture ligne par ligne
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            int val;
            if (fscanf(file, "%d", &val) != 1) {
                printf("Erreur de lecture dans le fichier à la position (%d, %d).\n", i, j);
                fclose(file);
                return;
            }
            grille[i][j] = (val != 0); // Convertir en booléen
        }
    }

    fclose(file); // Fermer le fichier
    printf("Grille chargée depuis '%s'.\n", nom_fichier);
}

void *safe_malloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Erreur : allocation mémoire échouée\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}
