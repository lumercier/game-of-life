#include <stdio.h>
#include "stack.h"

Stack *init_stack(int capacity) {
    Stack *stack = malloc(sizeof(Stack));
    stack->data = malloc(capacity * sizeof(bool **));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void push(Stack *stack, bool **grille, int lignes, int colonnes) {
    if (stack->top >= stack->capacity - 1) {
        fprintf(stderr, "Pile pleine\n");
        return;
    }
    bool **copy = malloc(lignes * sizeof(bool *));
    for (int i = 0; i < lignes; i++) {
        copy[i] = malloc(colonnes * sizeof(bool));
        memcpy(copy[i], grille[i], colonnes * sizeof(bool));
    }
    stack->data[++stack->top] = copy;
}

bool **pop(Stack *stack) {
    if (stack->top < 0) {
        fprintf(stderr, "Pile vide\n");
        return NULL;
    }
    return stack->data[stack->top--];
}

void free_stack(Stack *stack, int lignes) {
    for (int i = 0; i <= stack->top; i++) {
        for (int j = 0; j < lignes; j++) {
            free(stack->data[i][j]);
        }
        free(stack->data[i]);
    }
    free(stack->data);
    free(stack);
}

