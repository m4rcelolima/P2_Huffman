#include "decompress.h"

/*
 * Function: decompress
 * -------------------------------------------------
 * file_array: An array containing the bytes of the original file
 * file_size: The amount of bytes the original file had, and the size of file_array
 * output: The name of the compressed file, that is going to be created
*/
void decompress(unsigned char *file_array, long int file_size, const char *output){

    unsigned char first_byte = file_array[0];
    unsigned char second_byte = file_array[1];

    int trash = (file_array[0] >> 5);

    //removing trash bits
    first_byte = (first_byte << 3);
    first_byte = (first_byte >> 3);

    int tree_size = first_byte;
    tree_size = (tree_size << 8);
    tree_size |= second_byte;

    pqueue* tree_data = createPQueue();
    long int i;
    for (i = 1; i <= tree_size; i++){
        enqueue(tree_data, newNode(file_array[i+1], i, NULL, NULL));
    }

    node* huffman_tree = recreateHuffmanTree(tree_data);
    free(tree_data);

    FILE* decompressed = fopen(output, "w");
    node* tree_position = huffman_tree;

    for (i = tree_size+2; i < file_size -1; i++){
        tree_position = writeByte(tree_position, huffman_tree, decompressed, file_array[i], 0);
    }
    writeByte(tree_position, huffman_tree, decompressed, file_array[i], trash);

    fclose(decompressed);

    printf("All done!\n");

}

/*
 * Function: isSeted
 * -------------------------------------------------
 * byte: the byte to check whether or not a bit is set
 * i: the bit to be checked, from right to left
 * return: 1 if it's set, 0 if not set
*/
int isSeted(unsigned char byte, int i){
    unsigned char temp = 1 << i;
    return temp & byte;
}


/*
 * Function: writeByte
 * -------------------------------------------------
 * Traverses the huffman tree to find the byte to be writed in the decompressed file
 * -------------------------------------------------
 * tree_position: the current node in the huffman tree traversal
 * tree_root: the root of the huffman tree
 * decompressed_file: the file where the bytes are going to be writen
 * byte: byte of the compressed file (.huff) currently being read
 * trash: amount of bits that are "trash" in the last byte
*/
node* writeByte(node* tree_position, node* tree_root, FILE* decompressed_file, unsigned char byte, int trash){

    int i = 8;
    while (i > trash){
        i--;

        if (isSeted(byte, i)){
            tree_position = tree_position->right;
        }
        else{
            tree_position = tree_position->left;
        }

        if (tree_position->left == NULL && tree_position->right == NULL){
            putc(getItem(tree_position), decompressed_file);
            tree_position = tree_root;
        }
    }
    return tree_position;
}

/*
 * Function: recreateHuffmanTree
 * -------------------------------------------------
 * Recreates the huffman tree
 * -------------------------------------------------
 * tree_data: a queue containing the tree bytes
*/
node* recreateHuffmanTree(pqueue* tree_data){

    node* current = dequeue(tree_data);

    if (getItem(current) == '*'){
        node* left = recreateHuffmanTree(tree_data);
        node* right = recreateHuffmanTree(tree_data);
        return newNode(getItem(current), 0, left, right);
    }
    else{
        if (getItem(current) == '\\'){
            current = dequeue(tree_data);
        }
        return newNode(getItem(current), 0, NULL, NULL);
    }
}