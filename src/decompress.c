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

            decompressed = fopen(decompressed_name, 'wb');

            fread(&header, sizeof(unsigned short int), 1, toDescompress);

            trash = header >> 13;

            tree_size = header << 3;

            tree_size = tree_size >> 3;

            printf("Initiating decompressing on file: %s...\n", file_name);
        }
    }
    //placeholder
    printf("decompress function called\n");

}
