#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
//
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
        perror("Cannot allocate memory\n");
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
            perror("Cannot allocate memory\n");
            exit(EXIT_FAILURE);
        }
        new_node->data = malloc(data_size);
        if (new_node->data == NULL) {
            perror("Cannot allocate memory\n");
            exit(EXIT_FAILURE);
        }
        memcpy(new_node->data, val, data_size);
        new_node->next = list->head;
        list->head = new_node;
        list->size++;
    }
    return list;
}

void *assign_from_range(List *list, void *array, size_t n, size_t data_size) {
    for (int i = 0; i < n; ++i) {
        Node *new_node = (Node *)malloc(sizeof(Node));
        if (new_node == NULL) {
            perror("Cannot allocate memory\n");
            exit(EXIT_FAILURE);
        }
        new_node->data = malloc(data_size);
        if(new_node->data == NULL) {
            perror("Cannot allocate memory\n");
            exit(EXIT_FAILURE);
        }
        memcpy(new_node->data, (char *)array + i*data_size, data_size);
        new_node->next = list->head;
        list->head = new_node;
        list->size++;
    }
}

void *front(List *list) {
    if (list->head == NULL) {
        printf("Link List Empty.\n");
        return NULL;
    }
    return list->head->data;
}

void *back(List *list) {
    if (list->head == NULL) {
        printf("Link List Empty.\n");
        return NULL;
    }
    Node *currency = list->head;
    while (currency->next != NULL) {
        currency = currency->next;
    }
    return currency->data;
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
    int size = 12;
    int a[12];
    List *list = init_empty_list();
    for (int i = 0; i < 12; i++) {
        a[i] = i;
    }
    assign_from_range(list, a, size, sizeof(int));
    Node *current = list->head;
    while (current != NULL) {
        printf("Value: %d\n", *(int *)current->data);
        current = current->next;
    }
    int *front_val = front(list);
    int *back_val = back(list);
    printf("Front: %d\n", *front_val);
    printf("Back: %d\n", *back_val);
    free_list(list);
    return 0;
}
