#ifndef HISTORIQUE_H
#define HISTORIQUE_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Structure pour un nœud dans la liste doublement chaînée
typedef struct Node {
    bool **grille;       // Grille actuelle
    struct Node *prev;   // Pointeur vers le nœud précédent
    struct Node *next;   // Pointeur vers le nœud suivant
} Node;

// Structure pour la liste doublement chaînée
typedef struct {
    Node *head;  // Début de la liste
    Node *tail;  // Fin de la liste
    Node *current; // Position actuelle dans l'historique
    int lignes;
    int colonnes;
} Historique;

// Fonctions pour manipuler l'historique
Historique *init_historique(int lignes, int colonnes);
void ajouter_generation(Historique *historique, bool **grille);
bool **generation_precedente(Historique *historique);
bool **generation_suivante(Historique *historique);
void free_historique(Historique *historique);

#endif

