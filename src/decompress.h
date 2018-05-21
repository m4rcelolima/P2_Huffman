#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

#ifndef __DECOMPRESS_H_
#define __DECOMPRESS_H_

/*
 * Decompresses the file
*/
void decompress(unsigned char *file_array, long int file_size, const char *output);

/*
 * Recreats the Huffman Tree
*/
node* recreateHuffmanTree(pqueue* tree_data);

/*
 * Write the decoded bytes in the decompressed file
*/
node* writeByte(node* tree_position, node* tree_root, FILE* decompressed_file, unsigned char byte, int trash);

/*
 * Check if a bit is set
*/
int isSeted(unsigned char byte, int i);

#endif //__DECOMPRESS_H_