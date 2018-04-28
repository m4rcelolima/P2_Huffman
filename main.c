/*
 * This is a prototype 'main.c' for the Huffman Project
 * Data Structures class, Professor Marcio Ribeiro
 * Made by:
 * Bruno Rafael Severo
 * Marcelo Lima
 * Thiago Miranda
*/

#include <stdio.h>
#include <string.h>
#include "compress.h"

// Receives an error code and prints an error message
void argumentError(int e){
	switch (e){
		case 1:
			printf("Please use 3 arguments as follows:\n\n");
			printf("Example 1: ./huffman compress picture.png pic.huff\n");
			printf("Example 2: ./huffman decompress pic.huff picture.png\n");
			printf("\nEnding program.\n");
			break;
		case 2:
			printf("Invalid arguments.\n");
			break;
		default:
			printf("Error #%d\n", e);
	}
}

int main(int argc, char const *argv[]){

	/* 
	 * If the number of arguments is different than 3,
	 * prints out instructions and ends the program.
	*/
	if (argc != 4){
		argumentError(1);
		return 0;
	}

	/*
	 * Compress the file if the 'compress' argument
	 * is used.
	*/
	if ( !strcmp(argv[1], "compress") ){
		compress(argv[2], argv[3]);
	}

	/*
	 * Decompress the file if the 'decompress'
	 * argument is used.
	*/
	else if ( !strcmp(argv[1], "decompress") ){
		printf("Decompressing file...\n");
		//decompress(argv[2], argv[3]);
	}
	//Invalid argument
	else
		argumentError(2);
	return 0;
}
