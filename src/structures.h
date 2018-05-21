#include <stdlib.h>
#include <stdio.h>

#ifndef __STRUCTURES_H_
#define __STRUCTURES_H_

typedef struct _huffman{
    void *item;
    long int frequency;
    struct _huffman *next;
    struct _huffman *left;
    struct _huffman *right;
} node;

typedef struct _queue{
    node *head;
    int size;
} pqueue;


/*
 * Creates a new node and returns it
*/
node* newNode(unsigned char byte, long int freq, node* left, node* right);

/*
 * Initializes a priotity queue
*/
pqueue *createPQueue();

/*
 * Enqueues a node in a priority queue
*/
void enqueue(pqueue *q, node *new_node);

/*
 * Dequeues the first node from a queue
*/
node* dequeue(pqueue *q);

void printQueue(pqueue*);

void testQueue();

/*
 * Casts the void pointer to unsigned char from a node
*/
unsigned char getItem(node *node);

/*
 * Retuns the frequency of a node
*/
long int getFrequency(node *node);

#endif //__STRUCTURES_H_