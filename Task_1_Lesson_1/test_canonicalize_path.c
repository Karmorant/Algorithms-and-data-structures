#include "canonicalize_path.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char* canonicalize_path(const char *path);

int main() {
    char input[PATH_MAX];

    if (fgets(input, PATH_MAX, stdin)) {
        input[strcspn(input, "\n")] = '\0';
        char *canonical_path = canonicalize_path(input);
        printf("%s\n", canonical_path);
        free(canonical_path);
    } else {
        fprintf(stderr, "Error reading input from stdin.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}