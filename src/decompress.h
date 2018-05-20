#include "structures.h"

void decompress(char *);

void getBinaryTree(huffmanTree_t *, FILE *, unsigned short int);

void saveDecompress(FILE *, FILE *, huffmanTree_t *, unsigned short int);

bool isBitSet(unsigned char, short int);
