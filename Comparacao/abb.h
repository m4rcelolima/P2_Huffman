#include <stdio.h>
#include <stdlib.h>

#ifndef ABB_H
#define ABB_H

typedef struct abb_node ABB;

ABB *newNode(int item);

void inorder(ABB *root);

ABB* insert_abb(ABB *node, int item);

ABB* search_abb(ABB *root, int item, int*op);

void free_abb(ABB *root);
#endif /* ABB_H */
