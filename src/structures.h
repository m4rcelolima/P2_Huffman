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

typedef struct _huffmanTree{
    void *size;

    void *nodes;

    node *head;

    node *tail;
} huffmanTree;

node *newNode(unsigned char, long int, node*, node*);

pqueue *createPQueue();

void enqueue(pqueue*, node*);

node *dequeue(pqueue*);

void printQueue(pqueue*);

void testQueue();

unsigned char getItem(node*);

long int getFrequency(node*);

node *createEmptyBinaryTree();

void addHuffmanTree(huffmanTree *, node *);

void nextSet();
#endif
