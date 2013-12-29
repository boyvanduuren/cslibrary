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

int main() {
    struct node* root = build123_c();
    insert(root, 12);
    insert(root, 0);

    printf("root->data: %d\nroot->left->data: %d\nroot->right->data: %d\n",
        root->data, root->left->data, root->right->data);

    printf("size of tree: %d\n", size(root));

    return 0;
}
