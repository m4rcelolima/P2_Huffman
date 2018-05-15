#include "structures.h"

void compress(unsigned char*, long int, const char*);

void writeTree(node *huffman_tree, FILE *compressed_file, int *tree_size);

node *createHuffmanTree(unsigned char *file_array, long int file_size);

void mapHuffman(node *huffman_tree, node *coding[], char *bits, char *nextBit);

void addHuffmanCoding(node **coding, char item);