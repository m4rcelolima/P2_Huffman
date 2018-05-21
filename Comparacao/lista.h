#include <stdio.h>
#include <stdlib.h>

#ifndef LISTA_H
#define LISTA_H

typedef struct node Node;

Node* create_linked_list();

Node* insert_node(Node *first, int item);

Node* remove_node(Node *first, int item);

int is_empty(Node *first);

Node* search_node(Node *first, int item, int *op);

void print_linked_list(Node *first);

void free_list(Node *head);

#endif /* LISTA_H */
