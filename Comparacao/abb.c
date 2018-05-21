#include "abb.h"

struct abb_node
{
    int item;
    struct abb_node *left, *right;
};

// A utility function to create a new BST node
ABB *newNode(int item)
{
    ABB *temp =  (ABB *)malloc(sizeof(ABB));
    temp->item = item;
    temp->left = temp->right = NULL;
    return temp;
}

// A utility function to do inorder traversal of BST
void inorder(ABB *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d \n", root->item);
        inorder(root->right);
    }
}

/* A utility function to insert a new node with given key in BST */
ABB* insert_abb(ABB* node, int item)
{
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(item);

    /* Otherwise, recur down the tree */
    if (item < node->item)
        node->left  = insert_abb(node->left, item);
    else if (item > node->item)
        node->right = insert_abb(node->right, item);

    /* return the (unchanged) node pointer */
    return node;
}

// C function to search a given key in a given BST
ABB* search_abb(ABB *root, int item, int*op)
{
    (*op)++;
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->item == item)
       return root;

    // Key is greater than root's key
    if (root->item < item)
       return search_abb(root->right, item, op);

    // Key is smaller than root's key
    return search_abb(root->left, item, op);
}

void free_abb(ABB *root){
    if(root == NULL){
        return;
    }
    free_abb(root->left);
    free_abb(root->right);
    free(root);
}
