#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    size_t size;
} List;

List *init_empty_list() {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        perror("Error: Cannot allocate memory\n");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

List *init_value_list(size_t n, void *val, size_t data_size) {
    List *list = init_empty_list();
    for (int i = 0; i < n; ++i) {
        Node *new_node = (Node *)malloc(sizeof(Node));
        if (new_node == NULL) {
            perror("Error: Cannot allocate memory\n");
            exit(EXIT_FAILURE);
        }
        new_node->data = malloc(data_size);
        if (new_node->data == NULL) {
            perror("Error: Cannot allocate memory\n");
            exit(EXIT_FAILURE);
        }
        memcpy(new_node->data, val, data_size);
        new_node->next = list->head;
        list->head = new_node;
        list->size++;
    }
    return list;
}

void free_list(List *list) {
    if (list == NULL) return;

    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
    list->head = NULL;
    list->size = 0;
    free(list);
}

int main() {
    int size = 10;
    int value = 20;
    List *list = init_value_list(size, &value, sizeof(int));
    Node *current = list->head;
    while (current != NULL) {
        printf("Value: %d\n", *(int *)current->data);
        current = current->next;
    }
    free_list(list);
    return 0;
}