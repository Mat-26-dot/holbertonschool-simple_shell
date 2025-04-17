#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

typedef struct PathNode {
    char *dir;
    struct PathNode *next;  //object to pathnode
} PathNode;

char *_getenv(const char *name)
{
        size_t len = (strlen(name));
        for (char **env = environ; *env != NULL; env++)
        {
                if (strncmp(*env, name, len) == 0 && (*env)[len] == '=')
                        return (*env + len + 1);
        }

        return NULL;
}

PathNode *build_path_list(void) {
    char *path = _getenv("PATH");
    if (!path) return NULL;

    char *copy = strdup(path);
    char *token = strtok(copy, ":");

    PathNode *head = NULL, *tail = NULL;

    while (token) {
        PathNode *node = malloc(sizeof(PathNode));
        node->dir = strdup(token);
        node->next = NULL;

        if (!head) head = node;
        else tail->next = node; //if head is empty: makes our new node the head. If there is already a head, it is assigned as the tail
        tail = node;

        token = strtok(NULL, ":");
    }

    free(copy);
    return head;
}

void print_list(PathNode *head) {
    while (head) {
        printf("%s\n", head->dir);
        head = head->next;
    }
}

void free_list(PathNode *head) {
    PathNode *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp->dir);
        free(temp);
    }
}

int main(void) {
    PathNode *list = build_path_list();
    print_list(list);
    free_list(list);
    return 0;
}
