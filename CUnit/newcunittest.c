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
#include "../src/structures.h"

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
    node *new_node = newNode('A', 1, NULL, NULL);
    
    enqueue(queue, new_node);

    CU_ASSERT(getItem(queue->head) == 'A');
    CU_ASSERT(getFrequency(queue->head) == 1);
    
    dequeue(queue);
    
    CU_ASSERT(getItem(queue->head) == NULL);
    CU_ASSERT(getFrequency(queue->head) == NULL);
    
    enqueue(queue, new_node);
    new_node = newNode('D', 4, NULL, NULL);
    enqueue(queue, new_node);
    new_node = newNode('B', 2, NULL, NULL);
    enqueue(queue, new_node);
    new_node = newNode('C', 3, NULL, NULL);
    enqueue(queue, new_node);

    
    CU_ASSERT(getItem(queue->head) == 'A');
    CU_ASSERT(getFrequency(queue->head) == 1);
    
    dequeue(queue);

    CU_ASSERT(getItem(queue->head) == 'B');
    CU_ASSERT(getFrequency(queue->head) == 2);
    
    dequeue(queue);
    
    CU_ASSERT(getItem(queue->head) == 'C');
    CU_ASSERT(getFrequency(queue->head) == 3);
    
    dequeue(queue);
    
    CU_ASSERT(getItem(queue->head) == 'D');
    CU_ASSERT(getFrequency(queue->head) == 4);
    
    dequeue(queue);
}


void treeTest(){

  node *tree = newNode('6', 1, 
          newNode('4', 2, 
            newNode('3', 3, NULL, NULL), newNode('5', 4, NULL, NULL)), 
          newNode('8', 5, 
            newNode('7', 6, NULL, NULL), newNode('9', 7, NULL, NULL)));
  
  CU_ASSERT(getItem(tree) == '6');
  
  CU_ASSERT(getFrequency(tree) == 1);
  
  CU_ASSERT(getItem(tree->left) == '4');
  
  CU_ASSERT(getFrequency(tree->left) == 2);
  
  CU_ASSERT(getItem(tree->right) == '8');
  
  CU_ASSERT(getFrequency(tree->right) == 5);
  
  CU_ASSERT(getItem(tree->left->left) == '3');
  
  CU_ASSERT(getFrequency(tree->left->left) == 3);
  
  CU_ASSERT(getItem(tree->left->right) == '5');
  
  CU_ASSERT(getFrequency(tree->left->right) == 4);
 
  CU_ASSERT(getItem(tree->right->left) == '7');
  
  CU_ASSERT(getFrequency(tree->right->left) == 6);
  
  CU_ASSERT(getItem(tree->right->right) == '9');

  CU_ASSERT(getFrequency(tree->right->right) == 7);

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