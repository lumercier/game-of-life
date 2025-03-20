#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Structure pour la pile
typedef struct Stack {
    bool ***data;
    int top;
    int capacity;
} Stack;

// Prototypes des fonctions pour la gestion de la pile
Stack *init_stack(int capacity);
void push(Stack *stack, bool **grille, int lignes, int colonnes);
bool **pop(Stack *stack);
void free_stack(Stack *stack, int lignes);

#endif

