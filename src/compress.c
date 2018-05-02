#include <stdio.h>
#include <stdlib.h>
#include "compress.h"

//NOTE: compressedSize() is not tested

/*
 * Function: compress
 * -------------------------------------------------
 * file_array: A array containing the bytes of the original file
 * file_size: The amount of bytes the original file had, and the size of file_array
 * output: The name of the compressed file, that is going to be created
*/
void compress(unsigned char *file_array, long int file_size, const char* output){


    //placeholder
    printf("compress function called\n");
   
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