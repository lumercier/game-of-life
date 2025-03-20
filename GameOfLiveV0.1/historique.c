#include "historique.h"
#include <stdio.h>

// Initialiser l'historique
Historique *init_historique(int lignes, int colonnes) {
    Historique *historique = malloc(sizeof(Historique));
    historique->head = NULL;
    historique->tail = NULL;
    historique->current = NULL;
    historique->lignes = lignes;
    historique->colonnes = colonnes;
    return historique;
}

// Ajouter une génération à l'historique
void ajouter_generation(Historique *historique, bool **grille) {
    // Créer une copie de la grille
    bool **copy = malloc(historique->lignes * sizeof(bool *));
    for (int i = 0; i < historique->lignes; i++) {
        copy[i] = malloc(historique->colonnes * sizeof(bool));
        memcpy(copy[i], grille[i], historique->colonnes * sizeof(bool));
    }

    // Créer un nouveau nœud
    Node *new_node = malloc(sizeof(Node));
    new_node->grille = copy;
    new_node->prev = historique->current;
    new_node->next = NULL;

    // Ajouter à la liste
    if (historique->current) {
        // Si on n'est pas à la fin, supprimer les générations futures
        Node *temp = historique->current->next;
        while (temp) {
            Node *to_delete = temp;
            temp = temp->next;
            for (int i = 0; i < historique->lignes; i++) {
                free(to_delete->grille[i]);
            }
            free(to_delete->grille);
            free(to_delete);
        }
        historique->current->next = new_node;
    } else {
        historique->head = new_node;
    }

    historique->current = new_node;
    historique->tail = new_node;
}

// Revenir à la génération précédente
bool **generation_precedente(Historique *historique) {
    if (historique->current && historique->current->prev) {
        historique->current = historique->current->prev;
        return historique->current->grille;
    }
    return NULL;
}

// Avancer à la génération suivante
bool **generation_suivante(Historique *historique) {
    if (historique->current && historique->current->next) {
        historique->current = historique->current->next;
        return historique->current->grille;
    }
    return NULL;
}

// Libérer toute la mémoire de l'historique
void free_historique(Historique *historique) {
    Node *temp = historique->head;
    while (temp) {
        Node *to_delete = temp;
        temp = temp->next;
        for (int i = 0; i < historique->lignes; i++) {
            free(to_delete->grille[i]);
        }
        free(to_delete->grille);
        free(to_delete);
    }
    free(historique);
}

