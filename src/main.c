/*
 * Huffman Project
 * Data Structures class, Professor Marcio Ribeiro
 * Made by:
 * Bruno Rafael Severo
 * Marcelo Lima
 * Thiago Miranda
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "compress.h"
#include "decompress.h"
#include "structures.h"

#define TESTQUEUE 0

// Receives an error code and prints an error message
void printError(int e){
	switch (e){
		case 1:
			printf("Please use 3 arguments as follows:\n\n");
			printf("Example 1: ./huffman compress picture.png pic.huff\n");
			printf("Example 2: ./huffman decompress pic.huff picture.png\n");
			break;
		case 2:
			printf("Invalid arguments\n");
			break;
		case 3:
			printf("Error reading file\n");
			break;
		default:
			printf("Error #%d\n", e);
	}
}

int main(int argc, char const *argv[]){

	if (TESTQUEUE){
		testQueue();
		return 0;
	}

	/*
	 * If the number of arguments is different than 3,
	 * prints out instructions and ends the program.
	*/
	if (argc != 4){
		printError(1);
        return 0;
	}

	// Open file in read mode
	FILE *input = fopen(argv[2], "r");


	if (input == NULL){
		printError(3);
		return 0;
	}

	/*
	 * Sets cursor to end of file
	 * Get the file size from the position of the cursor
	 * Resets cursor to the beggining
	*/
	fseek(input, 0 ,SEEK_END);
	long int file_size = ftell(input);
	fseek(input, 0, SEEK_SET);

	/*
	 * Allocates an array with the size of the file in bytes
	 * Copies the file bytes to the array
	 * Closes the file
	*/
	unsigned char *file_data = (unsigned char*) malloc(file_size * sizeof(unsigned char));
	fread(file_data, sizeof(char), file_size, input);
	fclose(input);


	printf("The file %s has %ld bytes\n", argv[2], file_size);


	/*
	 * Compress the file if the 'compress' argument
	 * is used.
	*/
	if ( !strcmp(argv[1], "compress") ){
        printf("\nCompressing the file: %s...\n\n", argv[2]);
		compress(file_data, file_size, argv[3]);
	}

	/*
	 * Decompress the file if the 'decompress'
	 * argument is used.
	*/
	else if ( !strcmp(argv[1], "decompress") ){
        printf("\nDecompressing the file: %s\n\n", argv[2]);
		decompress(file_data, file_size, argv[3]);
	}
	//Invalid argument
	else
		printError(2);
	return 0;
}
