#include "browser_history.h"
#include <stdio.h>
#include <string.h>

int main() {
    BrowserHistory *history = create_browser_history();
    char command[MAX_COMMAND_LENGTH];
    char url[MAX_URL_LENGTH];
    int steps;

    while (fgets(command, MAX_COMMAND_LENGTH, stdin)) {
        if (sscanf(command, "visit %20s", url) == 1) {
            if (strlen(url) > 20) {
                fprintf(stderr, "Error: URL length exceeds 20 characters.\n");
                continue;
            }
            visit(history, url);
            print_history(history);
        } else if (sscanf(command, "back %d", &steps) == 1) {
            if (steps < 0 || steps > 100) {
                fprintf(stderr, "Error: Invalid number of steps for 'back' command.\n");
                continue;
            }
            back(history, steps);
            print_history(history);
        } else if (sscanf(command, "forward %d", &steps) == 1) {
            if (steps < 0 || steps > 100) {
                fprintf(stderr, "Error: Invalid number of steps for 'forward' command.\n");
                continue;
            }
            forward(history, steps);
            print_history(history);
        } else {
            fprintf(stderr, "Error: Invalid command.\n");
        }
    }

    free_browser_history(history);
    return 0;
}