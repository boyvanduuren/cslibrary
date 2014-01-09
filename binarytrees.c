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

// Given a binary tree, print out the nodes of the tree
// according to a bottom-up "postorder" traversel -- both
// subtrees of a node are printed out completely before the node
// itself is printed, and each left subtree is printed before the right
void printPostorder(struct node* node) {
    if (!node) return;
    else {
        printPostorder(node->left);
        printPostorder(node->right);
        printf("%d ", node->data);
    }
}

// We'll define a "root-to-leaf path" to be a sequence of nodes
// in a tree starting with the root node and proceeding downward
// to a leaf (a node with no children). We'll say that an empty
// tree contains no root-to-leaf paths.
// For this problem, we will be concerned with the sum
// of the values of such a path
int hasPathSum(struct node* node, int sum) {
    // Follow every node till we find a leaf node
    // subtracting the value of each node from sum
    if (!node->left && !node->right) {
        if (sum - node->data == 0) return 1;
        else return 0;
    }

    return (hasPathSum(node->left, sum - node->data) ||
        hasPathSum(node->right, sum - node->data));
}

// Given a binary tree, print out all of its root-to-leaf paths as defined above
// use this by calling printPaths(struct node* node)
void printPathsRecur(struct node* node, int pathLen) {
    int i;
    static int path[1000];

    if (!node) return;

    path[pathLen] = node->data;
    pathLen++;

    if (!node->left && !node->right) {
        for (i = 0; i < pathLen; i++)
            printf("%d ", path[i]);
        printf("\n");
    }

    printPathsRecur(node->left, pathLen);
    printPathsRecur(node->right, pathLen);
}

void printPaths(struct node* node) {
    printPathsRecur(node, 0);
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

    printPostorder(root);
    printf("\n");

    if (hasPathSum(root, 9)) printf("Tree has a root-to-leaf path that sums to 9\n");
    printPaths(root);

    return 0;
}
