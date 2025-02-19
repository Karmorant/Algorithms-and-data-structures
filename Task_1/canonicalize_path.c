#include "canonicalize_path.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Stack* create_stack(int capacity) {
    Stack *stack = malloc(sizeof(Stack));
    stack->items = malloc(capacity * sizeof(char*));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void push(Stack *stack, const char *item) {
    if (stack->top >= stack->capacity - 1) {
        fprintf(stderr, "Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    stack->items[++stack->top] = strdup(item);
}

char* pop(Stack *stack) {
    return (stack->top == -1) ? NULL : stack->items[stack->top--];
}

void free_stack(Stack *stack) {
    for (int i = 0; i <= stack->top; i++) free(stack->items[i]);
    free(stack->items);
    free(stack);
}

char* canonicalize_path(const char *path) {
    if (!path) return NULL;

    Stack *stack = create_stack(PATH_MAX);
    char *path_copy = strdup(path);
    char *token = strtok(path_copy, "/");

    while (token != NULL) {
        if (strcmp(token, "..") == 0) {
            if (stack->top == -1) {
                fprintf(stderr, "Error: Going upper than the root directory is not possible.\n");
                free(path_copy);
                free_stack(stack);
                exit(EXIT_FAILURE);
            }
            free(pop(stack));
        } else if (strcmp(token, ".") != 0 && strlen(token) > 0) {
            push(stack, token);
        }
        token = strtok(NULL, "/");
    }

    char *canonical_path = malloc(PATH_MAX);
    strcpy(canonical_path, "/");

    for (int i = 0; i <= stack->top; i++) {
        strcat(canonical_path, stack->items[i]);
        if (i < stack->top) strcat(canonical_path, "/");
    }

    free(path_copy);
    free_stack(stack);
    return canonical_path;
}