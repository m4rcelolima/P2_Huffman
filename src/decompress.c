#include <stdio.h>
#include <stdlib.h>
#include "decompress.h"

void decompress(char *file_name){
    printf("\nDecompressing...\n");

    if(file_name != NULL){
        FILE* toDescompress = NULL;
        FILE* decompressed = NULL;

        toDescompress = fopen(file_name, "rb");

        if(toDescompress != NULL){
            unsigned short int header, trash, tree_size;

            char *decompressed_name = (char*) calloc(strlen(file_name), sizeof(char));

            strcpy(decompressed_name, file_name);

            decompressed_name[strlen(file_name) - 5] = '\0';

            decompressed = fopen(decompressed_name, "wb");

            fread(&header, sizeof(unsigned short int), 1, toDescompress);

            trash = header >> 13;

            tree_size = header << 3;

            tree_size = tree_size >> 3;

            printf("Initiating decompressing on file: %s...\n", file_name);
            printf("Forming tree...\n");

            huffmanTree *tree = createEmptyBinaryTree();
            getBinaryTree(tree, toDescompress, tree_size);

            printf("Tree formed!\n");
            printf("Decompressing...\n");

            saveDecompress(toDescompress, decompressed, tree, trash);
            printf("File decompressed!\n");

            fclose(toDescompress);
            fclose(decompressed);

            free(decompressed_name);

            destroyBinaryTree(tree);
        } else{
            printf("\nThe file %s was not found!\n", file_name);
        }
    }
}

void getBinaryTree(huffmanTree *tree, FILE *source, unsigned short int tree_size){

    if(tree != NULL && source != NULL){

        if(tree_size > 1){
            addHuffmanTree(tree, getNode(source));
        } else{
            addHuffmanTree(tree, newNode(AUX, 0, getNode(source), NULL));
        }
    }
}

node *getNode(FILE *source){
    if(source != NULL){

        unsigned char buffer;

        fread(&buffer, sizeof(unsigned char), 1, source);

        if (buffer == AUX) {

            return newNode(buffer, 0, getNode(source), getNode(source));
        } else if (buffer == ESC){
            fread(&buffer, sizeof(unsigned char), 1, source);
            return newNode(buffer, 0, NULL, NULL);
        } else{
            return newNode(buffer, 0, NULL, NULL);
        }
    } else{
        return NULL;
    }
}

void saveDecompress(FILE *source, FILE *destination, huffmanTree *tree, unsigned short int trash){
    if(source != NULL && destination != NULL && tree != NULL){

        unsigned char buffer;
        unsigned char aux;

        node *tmp = tree->head;

        fread(&buffer, sizeof(unsigned char), 1, source);

        while(!feof(source)){

            fread(&aux, sizeof(unsigned char), 1, source);

            short int i;
            for(i = 7; i >= 0; i--){
                if(!feof(source) || trash <= i){

                    if(isBitSet(buffer, i)){
                        tmp = tmp->right;
                    } else{
                        tmp = tmp->left;
                    }

                    if(isLeaf(tmp)){

                        unsigned char aux_tmp = *(unsigned char*)tmp->item;

                        tmp = tree->head;

                        fwrite(&aux_tmp, sizeof(unsigned char), 1, destination);
                    }
                }
            }
            buffer = aux;
        }
    }
}

int isBitSet(unsigned char base, short int i){
    unsigned char mask = 1 << i;

    return base & mask;
}
