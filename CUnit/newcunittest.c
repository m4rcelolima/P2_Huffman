/*
 * File:   newcunittest.c
 * Author: Thiago
 *
 * Created on 21/05/2018, 01:29:53
 */


//https://mysnippets443.wordpress.com/2015/03/07/ubuntu-install-cunit/
// gcc  -o teste teste.c  -lcunit


#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct _huffman{
    int item;
    int priority;
    int nNodes;
    struct _huffman *next;
    struct _huffman *left;
    struct _huffman *right;
} node;

typedef struct _queue{
    node *head;
    int size;
} pqueue;


pqueue* createPQueue(){
    pqueue *new_queue = (pqueue*)malloc(sizeof(pqueue));
    new_queue->head = NULL;
    new_queue->size = 0;
    return new_queue;
}

int is_empty(pqueue *pq){
    if(pq->size > 0) return 0;
    
    return 1;
}

void enqueue(pqueue *pq, int i, int p)
{
    node *new_node = (node*) malloc(sizeof(node));
    new_node->item = i;
    new_node->priority = p;
    new_node->right = NULL;
    new_node->left = NULL;
    new_node->nNodes = 0;
    if ((is_empty(pq)) || (p > pq->head->priority)) {
        new_node->next = pq->head;
        pq->head = new_node;
    } else {
        node *current = pq->head;
    while ((current->next != NULL) && (current->next->priority > p)) {
        current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
    }
}


int dequeue(pqueue *q){
    if (q->size < 1){
        printf("Queue underflow\n");
        return NULL;
    }
    else{
        node *dequeue = q->head;
        q->head = q->head->next;
        dequeue->next = NULL;
        q->size--;

        return dequeue->item;
    }
}

int checkSizeQueue(pqueue *pq){
    return pq->size;
}

// ÁRVORE

node* createEmptyBinaryTree(){
  return NULL;
}

node* createBinaryTree(int item, node *left, node *right){
  node *new_tree = (node*) malloc(sizeof(node));

  new_tree->nNodes = 1;
  new_tree->item = item;
  new_tree->left = left;
  new_tree->right = right;

  return new_tree;
}

bool isEmptyy(node *bt){
  if(bt == NULL) return true;
  else return false;
}

node* add(node *bt, int item){
  if(bt == NULL){
    bt = createBinaryTree(item, NULL, NULL);
  }else if(bt->item > item){
    bt->left = add(bt->left, item);
  }else{
    bt->right = add(bt->right, item);
  }
  bt->nNodes++;
  return bt;
}

int checkSizeTree(node *bt){
  if(bt == NULL){
    return 0;
  }else{
    return bt->nNodes;
  }
}



int init_suite(void)
{
    return 0;
}

int clean_suite(void)
{
    return 0;
}

void queueTest(){

    pqueue *queue = createPQueue();

    CU_ASSERT(checkSizeQueue(queue) == 0);
    
    CU_ASSERT(is_empty(queue) == 1);
    
    enqueue(queue, 10, 1);

    CU_ASSERT(checkSizeQueue(queue) == 1);

    CU_ASSERT(is_empty(queue == 0));
    
    CU_ASSERT(dequeue(queue) == 10);

    CU_ASSERT(checkSizeQueue(queue) == 1);

    CU_ASSERT(checkSizeQueue(queue) == 0);

    enqueue(queue, 20, 1);
    
    enqueue(queue, 5, 2);
    
    enqueue(queue, 1, 20);
    
    CU_ASSERT(checkSizeQueue(queue) == 3);
    
    CU_ASSERT(is_empty(queue == 0));
    
    CU_ASSERT(dequeue(queue) == 1);
    
    CU_ASSERT(checkSizeQueue(queue) == 2);
    
    CU_ASSERT(dequeue(queue) == 5);
    
    CU_ASSERT(checkSizeQueue(queue) == 1);
    
    CU_ASSERT(dequeue(queue) == 20);
    
    CU_ASSERT(is_empty(queue == 1));
    
    CU_ASSERT(checkSizeQueue(queue) == 0);

}


void treeTest(){

  node *bt = createEmptyBinaryTree();

  bt = createBinaryTree(10, NULL, NULL);

  CU_ASSERT(checkSizeTree(bt) == 1);

  add(bt, 14);

  CU_ASSERT(checkSizeTree(bt) == 2);

  add(bt, 19);

  CU_ASSERT(checkSizeTree(bt) == 3);


}

int main(){
  /* pSuite1 = lista
     pSuite3 = Árvore
 */

    CU_pSuite pSuite1 = NULL;

    if(CUE_SUCCESS != CU_initialize_registry() )
    {
        return CU_get_error();
    }

    // Adiciona suite1 para registro
    pSuite1 = CU_add_suite("queue_test_suite", init_suite, clean_suite);
    if (NULL == pSuite1)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Adiciona test1 para suite1
    if(NULL == CU_add_test(pSuite1, "queue_test_suit", queueTest)){
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Adiciona test1 para suite1
    if(NULL == CU_add_test(pSuite1, "tree_test_suit", treeTest)){
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    printf("\n");
    CU_basic_show_failures(CU_get_failure_list());

    CU_cleanup_registry();
    return CU_get_error();
}