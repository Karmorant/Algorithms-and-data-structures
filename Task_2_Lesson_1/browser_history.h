#ifndef BROWSER_HISTORY_H
#define BROWSER_HISTORY_H

#define MAX_URL_LENGTH 21
#define MAX_COMMAND_LENGTH 100


typedef struct Node {
    char url[MAX_URL_LENGTH];
    struct Node *prev;
    struct Node *next;
} Node;


typedef struct {
    Node *current;
} BrowserHistory;


BrowserHistory* create_browser_history();
void visit(BrowserHistory *history, const char *url);
void back(BrowserHistory *history, int steps);
void forward(BrowserHistory *history, int steps);
void print_history(BrowserHistory *history);
void free_browser_history(BrowserHistory *history);

#endif