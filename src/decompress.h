#include "structures.h"

void decompress(unsigned char *, long int, const char *);

node* recreateHuffmanTree(pqueue* tree_data);

node* writeByte(node* tree_position, node* tree_root, FILE* decompressed_file, unsigned char byte, int trash);

int isSeted(unsigned char byte, int i);