#ifndef CANONICALIZE_PATH_H
#define CANONICALIZE_PATH_H

#define PATH_MAX 4096

typedef struct {
    char **items;
    int top;
    int capacity;
} Stack;

Stack* create_stack(int capacity);
void push(Stack *stack, const char *item);
char* pop(Stack *stack);
void free_stack(Stack *stack);
char* canonicalize_path(const char *path);

#endif