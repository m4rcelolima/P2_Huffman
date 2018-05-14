#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compress.h"
#include "structures.h"

//Function to test the huffman coding
//TO BE REMOVED ONCE TESTING IS DONE
void test(node* huff[]){
    int i;
    printf("TESTING\n");
    for (i = 0; i < 256; i++){
        printf("[%d]: ", i);
        while(huff[i] != NULL){
            printf("%c", getItem(huff[i]));
            huff[i] = huff[i]->next;
        }
        printf("\n");
    }
}

//NOTE: compressedSize() is not tested
/*
 * Function: compress
 * -------------------------------------------------
 * file_array: An array containing the bytes of the original file
 * file_size: The amount of bytes the original file had, and the size of file_array
 * output: The name of the compressed file, that is going to be created
*/
void compress(unsigned char *file_array, long int file_size, const char *output){

    node* huffman_tree = createHuffmanTree(file_array, file_size);

    node* huffmanCoding[256] = {NULL};
    char* aux_string = (char*)calloc(17, sizeof(char));
    
    mapHuffman(huffman_tree, huffmanCoding, aux_string, "");

    test(huffmanCoding);


}

void mapHuffman(node* huffman_tree, node* coding[], char* bits, char* nextBit){
    strcat(bits, nextBit);
    if(huffman_tree->left == NULL && huffman_tree->right == NULL){
        int coding_size = strlen(bits);
        int i;
        for (i = 0; i < coding_size; i++){
            addHuffmanCoding(&coding[getItem(huffman_tree)], bits[i]);
        }
    }
    else{
        mapHuffman(huffman_tree->left, coding, bits, "0");
        bits[strlen(bits)-1] = '\0';
        mapHuffman(huffman_tree->right, coding, bits, "1");
        bits[strlen(bits)-1] = '\0';
    }
}

void addHuffmanCoding(node** coding, char item){
    if ( (*coding) == NULL ){
        (*coding) = newNode(item, 0, NULL, NULL);
        return;
    }
    addHuffmanCoding(&(*coding)->next, item);
}

/*
 * Function: createHuffmanTree
 * -------------------------------------------------
 * Takes the file data and finds the frequency of each byte,
 * then enqueues each byte with its frequency in a priority queue.
 * Dequeues the two lowest frequency bytes and makes them a child of
 * a '*' node with the sum of its frequencies. Then enqueues the parent
 * node back in the queue.
 * -------------------------------------------------
 * file_array: An array containing the bytes of the original file
 * file_size: The amount of bytes the original file had, and the size of file_array
 * return: Root of the huffman tree
*/
node* createHuffmanTree(unsigned char *file_array, long int file_size){
    long int byte_frequency[256] = {0};
    long int i;

    // counts the frequency of each byte
    for (i = 0; i < file_size; i++){
        byte_frequency[file_array[i]]++;
    }

    pqueue *priority_queue = createPQueue();

    // creates nodes with byte and frequency and enqueues them
    for (i = 0; i < 256; i++){
        if (byte_frequency[i] > 0){
            enqueue(priority_queue, newNode(i, byte_frequency[i], NULL, NULL) );
        }
    }

    // dequeues the two lowest priority nodes
    // and enqueues them back as childs of a
    // '*' node with the sum of their fequencies
    while (priority_queue->size > 1){
       
        node* left = dequeue(priority_queue);
        node* right = dequeue(priority_queue);

        enqueue(priority_queue, newNode('*', (left->frequency + right->frequency), left, right ) );
        
    }

    return priority_queue->head;

}


/*
 * Function: compressedSize
 * -------------------------------------------------
 * compressed_file: name of the .huff file
 * return: size of the file, or -1 if it can't be opened
*/
long int compressedSize(const char* compressed_file){
    FILE *cfile = fopen(compressed_file, "r");

    if (cfile == NULL){
        return -1;
    }

    fseek(cfile, 0, SEEK_END);
    long int csize = ftell(cfile);
    fclose(cfile);
    return csize;
}