#include <stdio.h>
#include <time.h>
#include <cstdlib>

typedef struct BSTnode{
    int val;
    struct BSTnode* right;
    struct BSTnode* left;
    struct BSTnode* parent;
} BSTnode;

void add_node(BSTnode* &root, int value){
    BSTnode* tmp = new BSTnode;
    tmp->val=value;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->parent = NULL;
    
    // If root is empty?
    if(root == NULL){
        root = tmp;
    }
    
    BSTnode* tmpRoot = root;
    BSTnode* prevRoot = NULL;
    BSTnode* todelete = prevRoot;
    
    // Find the father of a new node
    while(tmpRoot != NULL){
        prevRoot = tmpRoot;
        if (tmpRoot->val < value) tmpRoot = tmpRoot->left;
        else tmpRoot = tmpRoot->right;
    }
    
    // Insert the new node
    if(prevRoot->val < value)
        prevRoot->left = tmp;
    else{
        prevRoot->right = tmp;
    }
    
    delete todelete;
}

BSTnode* min(BSTnode* root){
    BSTnode *prevRoot = NULL;
    BSTnode *todelete = prevRoot;
    while (root != NULL) {
        prevRoot = root;
        root = root->left;
    }
    delete todelete;
    return prevRoot;
}

BSTnode* max(BSTnode* root){
    BSTnode *prevRoot = NULL;
    BSTnode *todelete = prevRoot;
    while (root != NULL) {
        prevRoot = root;
        root = root->right;
    }
    delete todelete;
    return prevRoot;
}

BSTnode* remove_node(BSTnode* root, int value){
    // When root is null
    if (root == NULL){
        return NULL;
    }
    // If value lies in left subtree
    if (value < root->val){
        root->left = remove_node(root->left, value);
    }
    // If value lies in right subtree
    else if (value > root->val){
        root->right = remove_node(root->right, value);
    }
    // if value is located in root node
    else{
        // node with only one child or no child
        if (root->left == NULL){
            BSTnode *tmp = root->right;
            free(root);
            return tmp;
        } else if (root->right == NULL){
            BSTnode *tmp = root->left;
            free(root);
            return tmp;
        }
        // node with two children: The inorder successor is the new value
        BSTnode* tmp = min(root->right);

        // Copy the inorder successor's content to this node
        root->val = tmp->val;

        // Delete the inorder successor
        root->right = remove_node(root->right, tmp->val);
    }
    return root;
}

void free_BST(BSTnode* root){
    if(root == NULL){
        return;
    }
    if(root->left != NULL){
        free_BST(root->left);
    }
    if(root->right != NULL){
        free_BST(root->right);
    }
    delete root;
    return;
}

void in_order_tree_walk(BSTnode* node){
    if(node->left != NULL){
        in_order_tree_walk(node->left);
    }
    printf("%d\n", node->val);
    if(node->right != NULL){
        in_order_tree_walk(node->right);
    }
}

int main(){
    /*
     * test data:
     * Z - number of test cases
     * N, X - number of insert values, number of deleted values
     * N values to insert
     * X values to remove
     * Output:
     * N-X lines od numberts
    */
    srand(time(NULL));
    int Z;
    scanf("%d", &Z);

    for(int i = 0 ; i < Z ; i++){
        int N, X;
        scanf("%d %d", &N, &X);

        BSTnode* tree = NULL;

        int x;
        // insert
        for(int j = 0 ; j < N ; j++) {
            scanf("%d", &x);
            add_node(tree, x);
        }
        // remove
        for(int j = 0 ; j < X ; j++) {
            scanf("%d", &x);
            tree = remove_node(tree, x);
        }

        in_order_tree_walk(tree);

        // cleanup
        free_BST(tree);
    }
}
