#include "structures.h"

void decompress(char *);

void getBinaryTree(huffmanTree *, FILE *, unsigned short int);

void saveDecompress(FILE *, FILE *, huffmanTree *, unsigned short int);

int isBitSet(unsigned char, short int);
