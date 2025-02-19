#include <stdio.h>
#include <assert.h>
#include <string.h>

extern char* canonicalize_path(const char *path);

void test_canonicalize_path() {
    // Тест 1
    assert(strcmp(canonicalize_path("/"), "/") == 0);

    // Тест 2
    assert(strcmp(canonicalize_path("/home/"), "/home") == 0);

    // Тест 3
    assert(strcmp(canonicalize_path("/home////////////////////Downloads/////"), "/home/Downloads") == 0);

    // Тест 4
    assert(strcmp(canonicalize_path("/home/./Downloads/Films/../Stories/"), "/home/Downloads/Stories") == 0);

    // Тест 5 (попытка выйти выше корня)
    printf("Expecting an error for the following test:\n");
    canonicalize_path("/../");

    printf("All tests passed!\n");
}

int main() {
    test_canonicalize_path();
    return 0;
}