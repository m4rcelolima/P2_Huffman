#include "structures.h"

/*
 * Function: newNode
 * -------------------------------------------------
 * Creates a new node and returns it 
 * byte: byte data from the file
 * freq: frequency of the byte
 * left: node on the left
 * right: node on the right
 * return: pointer to the new node
 */
node* newNode(unsigned char byte, long int freq, node* left, node* right){
    unsigned char *new_item = (unsigned char*)malloc(sizeof(unsigned char));
    *new_item = byte;
    node *new_node = (node*)malloc(sizeof(node));
    new_node->item = new_item;
    new_node->frequency = freq;
    new_node->next = NULL;
    new_node->left = left;
    new_node->right = right;
    return new_node;
}

/*
 * Function: createPQueue()
 * -------------------------------------------------
 * Creates a priority queue of huffman nodes, and returns it
 * return: pointer to the new priority queue
 */
pqueue* createPQueue(){
    pqueue *new_queue = (pqueue*)malloc(sizeof(pqueue));
    new_queue->head = NULL;
    new_queue->size = 0;
    return new_queue;
}

/*
 * Function: enqueue()
 * -------------------------------------------------
 * Enqueues nodes in a priority queue according to their byte frequency
 * *q: Priority queue
 * *new_node: Node to be enqueued
 */
void enqueue(pqueue *q, node *new_node){
    if (q->head == NULL){
        q->head = new_node;
        new_node->next = NULL;
    }
    else if (new_node->frequency <= q->head->frequency){
        new_node->next = q->head;
        q->head = new_node;
    }
    else{
        node* previous;
        node* current = q->head;
        while (current != NULL && new_node->frequency > current->frequency){
            previous = current;
            current = current->next;
        }
        new_node->next = current;
        previous->next = new_node;
    }
    q->size++;
}

/*
 * Function: dequeue()
 * -------------------------------------------------
 * Dequeues a node from a priority queue
 * *q: Priority queue
 * return: the dequeued node, or NULL if the queue is empty
 */
node* dequeue(pqueue *q){
    if (q->size < 1){
        printf("The queue is empty\n");
        return NULL;
    }
    else{
        node *dequeue = q->head;
        q->head = q->head->next;
        dequeue->next = NULL;
        q->size--;

        return dequeue;
    }
}

/*
 * Function: getItem()
 * -------------------------------------------------
 * Casts the void pointer to unsigned char and returns it
 */
unsigned char getItem(node *node){
    unsigned char *item = (unsigned char *)node->item;
    return *item;
}

/*
 * Function: getFrequency()
 * -------------------------------------------------
 * Returns the node frequency
 */
long int getFrequency(node *node){
    return node->frequency;
}

/*
 * Function: printQueue()
 * -------------------------------------------------
 * Prints the queue without altering it
 * *q: Priority queue
 */
void printQueue(pqueue *q){
    node* current = q->head;
    printf("|byte,frequency|\n");
    while (current != NULL){
        printf("|%c,%ld| ", getItem(current), current->frequency);
        current = current->next;
    }
    printf("\n");
}

/*
 * Function: testQueue()
 * -------------------------------------------------
 * This function's only purpose is to test the queue functionality
 * How to use: set TESTQUEUE to 1 in main.c file
 * Expected output:
 *              PRIORITY QUEUE TEST
 *              |byte,frequency|
 *              |d,10| |b,20| |c,30| |e,40| |a,50| 
 *              Dequeue: d|10
 *              Dequeue: b|20
 *              |byte,frequency|
 *              |c,30| |e,40| |a,50| 
 */
void testQueue(){
    unsigned char c[] = {'a','b','c','d','e'};
    long int f[] = {50,20,30,10,40};
    pqueue *q = createPQueue();
    int i;
    for (i = 0; i < 5; i++){
        enqueue(q, newNode(c[i], f[i], NULL, NULL) );
    }
    printf("\nPRIORITY QUEUE TEST\n");
    printQueue(q);
    for (i = 0; i < 2; i++){
        node *temp = dequeue(q);
        printf("Dequeue: %c|%ld\n", getItem(temp), getFrequency(temp) );
    }    
    printQueue(q);
}