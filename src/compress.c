#include "compress.h"

/*
 * Function: compress
 * -------------------------------------------------
 * file_array: An array containing the bytes of the original file
 * file_size: The amount of bytes the original file had, and the size of file_array
 * output: The name of the compressed file, that is going to be created
*/
void compress(unsigned char *file_array, long int file_size, const char *output){

    //Generates the Huffman Tree
    printf("Creating Huffman Tree...\n");
    node* huffman_tree = createHuffmanTree(file_array, file_size);

    //Mapping the new bits for each byte
    printf("Mapping the new bits...\n");
    node* huffmanCoding[256] = {NULL};
    char* aux_string = (char*)calloc(17, sizeof(char));
    mapHuffman(huffman_tree, huffmanCoding, aux_string, "");

    //Creates a new empty file and opens it in read and write mode
    FILE* compressed_file = fopen(output, "w+");

    //Initializing the first two bytes
    char first_byte = 0;
    char second_byte = 0;
    putc(first_byte, compressed_file);
    putc(second_byte, compressed_file);

    //Writing the Huffman Tree in the file in pre-order
    //and calculating the size of the tree
    int tree_size = 0;
    printf("Writing the Huffman Tree...\n");
    writeTree(huffman_tree, compressed_file, &tree_size);

    //Writing the contents of the file, with the new bit set
    //and getting the trash size
    printf("Writing the file contents...\n");
    int trash = writeCompressed(file_array, file_size, huffmanCoding, compressed_file);

    long int new_file_size = ftell(compressed_file);
    printf("Compressed file %s has %ld bytes\n", output, new_file_size);
    printf("A %.2f%% reduction!\n", (float)(file_size - new_file_size)/file_size*100.0);

    //Set the bits for the first two bytes with the trash size and tree size
    first_byte = tree_size >> 8;
    second_byte = tree_size;
    first_byte |= trash << 5;

    //Puts the cursor back in the beggining of the file and rewrites the
    //first two bytes
    fseek(compressed_file, 0, SEEK_SET);
    putc(first_byte, compressed_file);
    putc(second_byte, compressed_file);

    fclose(compressed_file);

}

/*
 * Function: writeTree
 * -------------------------------------------------
 * Writes the Huffman Tree, in pre-order, in the new compressed file
 * Uses '\' as the escape character for '*' and '\' in leaf nodes
 * Also calculates the tree size
 * -------------------------------------------------
 * huffman_tree: pointer to the huffman tree
 * compressed_file: pointer to the file where the huffman tree is going to be written
 * tree_size: pointer to a variable that holds the size of the tree
*/
void writeTree(node* huffman_tree, FILE* compressed_file, int* tree_size){
    if (huffman_tree != NULL){
        *tree_size += 1;
        if ( 
        (huffman_tree->left == NULL && huffman_tree->right == NULL) &&
        (getItem(huffman_tree) == '*' || getItem(huffman_tree) == '\\')
        ){
            *tree_size += 1;
            putc('\\', compressed_file);
        }
        putc(getItem(huffman_tree), compressed_file);
        writeTree(huffman_tree->left, compressed_file, tree_size);
        writeTree(huffman_tree->right, compressed_file, tree_size);
    }
}

/*
 * Function: writeCompressed
 * -------------------------------------------------
 * Writes the new bits for each byte of the original file
 * -------------------------------------------------
 * huffman_tree: pointer to the huffman tree
 * compressed_file: pointer to the file where the huffman tree is going to be written
 * tree_size: pointer to a variable that holds the size of the tree
 * return: the trash size;
*/
int writeCompressed(unsigned char* file_array, long int file_size, node* coding[], FILE* compressed_file){

    node* current;
    unsigned char byte = 0;
    int j = 7;
    long int i;

    //Goes through each byte of the original file
    for (i = 0; i < file_size; i++){
        current = coding[file_array[i]];
        for ( ; j >= 0; j--){
         
            if (getItem(current) == '1'){
                byte |= 1 << j;
            }

            //If all the new bits for the current byte have been written
            if (current->next == NULL){
                //If it's the last byte, write on the file and leave
                //j will be the trash size
                if (i == file_size-1){
                    putc(byte, compressed_file);
                    break;
                }
                //If there's enough bits to fill a byte
                //Write it on the file, resets the variables
                //And goes to the next byte
                else if(j == 0){
                    putc(byte, compressed_file);
                    byte = 0;
                    j = 7;
                    break;
                }
                //If the above is false, goes to next byte but keeps
                //current bit position
                else{
                    j--;
                    break;
                }
            }

            current = current->next;

            //If there's enough bits to fill a byte
            //Writes it on the file, resets the variables
            //And keep going
            if (j == 0){
                putc(byte, compressed_file);
                byte = 0;
                j = 8;
            }
        }
    }
    //The trash size
    return j;
}

/*
 * Function: mapHuffman
 * -------------------------------------------------
 * Get the new bits for every byte (leaf) in the tree
 * Stores them as chars in a linked list in a node* array
 * -------------------------------------------------
 * huffman_tree: pointer to the huffman tree
 * coding[]: an array of nodes, that is going to store the new bits
 * bits: string containing the current bits
 * nextBit: 0 if going to the left, 1 if going to the right
*/
void mapHuffman(node* huffman_tree, node* coding[], char* bits, char* nextBit){
    strcat(bits, nextBit);
    if(huffman_tree->left == NULL && huffman_tree->right == NULL){
        int coding_size = strlen(bits);
        int i;
        for (i = 0; i < coding_size; i++){
            addHuffmanCoding(&coding[getItem(huffman_tree)], bits[i]);
        }
    }
    else{
        mapHuffman(huffman_tree->left, coding, bits, "0");
        bits[strlen(bits)-1] = '\0';
        mapHuffman(huffman_tree->right, coding, bits, "1");
        bits[strlen(bits)-1] = '\0';
    }
}

/*
 * Function: addHuffmanCoding
 * -------------------------------------------------
 * Add the bit representations (char) in the end of a linked list
 * -------------------------------------------------
 * coding: double pointer to the head of the list
 * item: bit to be added
*/
void addHuffmanCoding(node** coding, char item){
    if ( (*coding) == NULL ){
        (*coding) = newNode(item, 0, NULL, NULL);
        return;
    }
    addHuffmanCoding(&(*coding)->next, item);
}

/*
 * Function: createHuffmanTree
 * -------------------------------------------------
 * Takes the file data and finds the frequency of each byte,
 * then enqueues each byte with its frequency in a priority queue.
 * Dequeues the two lowest frequency bytes and makes them a child of
 * a '*' node with the sum of its frequencies. Then enqueues the parent
 * node back in the queue.
 * -------------------------------------------------
 * file_array: An array containing the bytes of the original file
 * file_size: The amount of bytes the original file had, and the size of file_array
 * return: Root of the huffman tree
*/
node* createHuffmanTree(unsigned char *file_array, long int file_size){
    long int byte_frequency[256] = {0};
    long int i;

    // counts the frequency of each byte
    for (i = 0; i < file_size; i++){
        byte_frequency[file_array[i]]++;
    }

    pqueue *priority_queue = createPQueue();

    // creates nodes with byte and frequency and enqueues them
    for (i = 0; i < 256; i++){
        if (byte_frequency[i] > 0){
            enqueue(priority_queue, newNode(i, byte_frequency[i], NULL, NULL) );
        }
    }

    // dequeues the two lowest priority nodes
    // and enqueues them back as childs of a
    // '*' node with the sum of their fequencies
    while (priority_queue->size > 1){
        node* left = dequeue(priority_queue);
        node* right = dequeue(priority_queue);
        enqueue(priority_queue, newNode('*', (left->frequency + right->frequency), left, right ) );
    }

    return priority_queue->head;

}