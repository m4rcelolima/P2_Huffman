#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

#ifndef __COMPRESS_H_
#define __COMPRESS_H_

/*
 * Compresses the file
*/
void compress(unsigned char *file_array, long int file_size, const char *output);

/*
 * Generates a huffman tree and returns it
*/
node *createHuffmanTree(unsigned char *file_array, long int file_size);

/*
 * Writes the Huffman Tree in the new file
*/
void writeTree(node *huffman_tree, FILE *compressed_file, int *tree_size);

/*
 * Generates the new bits for each byte
*/
void mapHuffman(node *huffman_tree, node *coding[], char *bits, char *nextBit);

/*
 * Adds the new bits in a linked list
*/
void addHuffmanCoding(node **coding, char item);

/*
 * Writes the contents of the original file with the new bits
*/
int writeCompressed(unsigned char* file_array, long int file_size, node* coding[], FILE* compressed_file);

#endif //__COMPRESS_H_