#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
};

struct node* NewNode(int data) {
    struct node* node = malloc(sizeof(struct node));

    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

int lookup(struct node* node, int target) {
    if (!node) return 0;
    else {
        if (target == node->data) return 1;
        else {
            if (target < node->data) return lookup(node->left, target);
            else return lookup(node->right, target);
        }
    }
}

struct node* insert(struct node* node, int data) {
    if (!node) return NewNode(data);
    else {
        if (data <= node->data) node->left = insert(node->left, data);
        else node->right = insert(node->right, data);
    }

    return node;
}

/********************
 ** btree problems **
 ********************/

struct node* build123_a() {
    struct node* node1 = NewNode(1);
    struct node* node2 = NewNode(2);
    struct node* node3 = NewNode(3);

    node2->left = node1;
    node2->right = node3;

    return node2;
}

struct node* build123_b() {
    struct node* root = NewNode(2);

    root->left = NewNode(1);
    root->right = NewNode(3);

    return root;
}

struct node* build123_c() {
    struct node* root = insert(NULL, 2);
    insert(root, 1);
    insert(root, 3);

    return root;
}

int size(struct node* node) {
    static int count = 0;
    if (!node) return 0;
    else {
        count++;
        size(node->left);
        size(node->right);
    }
    return count;
}

int maxDepth(struct node* node) {
    if (!node) return 0;
    else {
        if (maxDepth(node->left) > maxDepth(node->right))
            return maxDepth(node->left) + 1;
        else
            return maxDepth(node->right) + 1;
    }
}

// Find the lowest value in an ordered binary tree
int minValue(struct node* node) {
    struct node* current = node;

    while(current->left) {
        current = current->left;
    }

    return current->data;
}

// Given a binary search tree iterate over
// all the nodes, printing them out in increasing order
void printTree(struct node* node) {
    if (!node) return;
    else {
        printTree(node->left);
        printf("%d ", node->data);
        printTree(node->right);
    }
}

int main() {
    struct node* root = NewNode(4);
    insert(root, 2);
    insert(root, 5);
    insert(root, 1);
    insert(root, 3);

    printf("size of tree: %d\n", size(root));
    printf("maxDepth of tree: %d\n", maxDepth(root));
    printf("minValue of tree: %d\n", minValue(root));
    printTree(root);
    printf("\n");

    return 0;
}
