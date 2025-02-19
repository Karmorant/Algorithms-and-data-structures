#include "browser_history.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

BrowserHistory* create_browser_history() {
    BrowserHistory *history = malloc(sizeof(BrowserHistory));
    history->current = malloc(sizeof(Node));
    strcpy(history->current->url, "homepage");
    history->current->prev = NULL;
    history->current->next = NULL;
    return history;
}


int is_valid_url(const char *url) {
    for (int i = 0; url[i] != '\0'; i++) {
        if (!isalnum(url[i]) && url[i] != '.') {
            return 0;
        }
    }
    return 1;
}


void visit(BrowserHistory *history, const char *url) {
    if (!is_valid_url(url)) {
        fprintf(stderr, "Error: Invalid URL. Only English letters, digits, and '.' are allowed.\n");
        return;
    }

    Node *new_node = malloc(sizeof(Node));
    strncpy(new_node->url, url, MAX_URL_LENGTH - 1);
    new_node->url[MAX_URL_LENGTH - 1] = '\0';

    while (history->current->next != NULL) {
        Node *temp = history->current->next;
        history->current->next = temp->next;
        free(temp);
    }

    new_node->prev = history->current;
    new_node->next = NULL;
    history->current->next = new_node;
    history->current = new_node;
}


void back(BrowserHistory *history, int steps) {
    while (steps > 0 && history->current->prev != NULL) {
        history->current = history->current->prev;
        steps--;
    }
}


void forward(BrowserHistory *history, int steps) {
    while (steps > 0 && history->current->next != NULL) {
        history->current = history->current->next;
        steps--;
    }
}


void print_history(BrowserHistory *history) {
    printf("%s\n", history->current->url);
}


void free_browser_history(BrowserHistory *history) {
    Node *current = history->current;
    while (current->prev != NULL) {
        current = current->prev;
    }
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(history);
}