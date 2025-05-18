#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

Node* createNode(int key) {
    Node* n = malloc(sizeof(Node));
    n->key = key; n->left = n->right = NULL;
    return n;
}

// Non-recursive insert
Node* insert(Node* root, int key) {
    Node *curr = root, *parent = NULL;
    Node* n = createNode(key);
    if (!root) return n;

    while (curr) {
        parent = curr;
        curr = (key < curr->key) ? curr->left : curr->right;
    }
    (key < parent->key) ? (parent->left = n) : (parent->right = n);
    return root;
}

// Non-recursive Preorder
void preorder(Node* root) {
    if (!root) return;
    Node* stack[MAX]; int top = -1;
    stack[++top] = root;
    printf("Preorder: ");
    while (top != -1) {
        Node* n = stack[top--];
        printf("%d ", n->key);
        if (n->right) stack[++top] = n->right;
        if (n->left)  stack[++top] = n->left;
    }
    printf("\n");
}

// Non-recursive Postorder using two stacks
void postorder(Node* root) {
    if (!root) return;
    Node *s1[MAX], *s2[MAX]; int top1 = -1, top2 = -1;
    s1[++top1] = root;
    while (top1 != -1) {
        Node* n = s1[top1--];
        s2[++top2] = n;
        if (n->left)  s1[++top1] = n->left;
        if (n->right) s1[++top1] = n->right;
    }
    printf("Postorder: ");
    while (top2 != -1) printf("%d ", s2[top2--]->key);
    printf("\n");
}

// Count total nodes (non-recursive)
int countNodes(Node* root) {
    if (!root) return 0;
    Node* stack[MAX]; int top = -1, count = 0;
    stack[++top] = root;
    while (top != -1) {
        Node* n = stack[top--];
        count++;
        if (n->right) stack[++top] = n->right;
        if (n->left)  stack[++top] = n->left;
    }
    return count;
}

// Display only leaf nodes (non-recursive)
void printLeafNodes(Node* root) {
    if (!root) return;
    Node* stack[MAX]; int top = -1;
    int count = 0;
    stack[++top] = root;
    printf("Leaf nodes: ");
    while (top != -1) {
        Node* n = stack[top--];
        if (!n->left && !n->right) printf("%d ", n->key);
        count++;
         printf("count is %d ", count);
        if (n->right) stack[++top] = n->right;
        if (n->left)  stack[++top] = n->left;
    }
    printf("\n");
}

// Main Menu
int main() {
    Node* root = NULL;
    int ch, key;
    while (1) {
        printf("\n1.Insert 2.Preorder 3.Postorder 4.Total Nodes 5.Leaf Nodes 6.Exit\nEnter: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: printf("Key: "); scanf("%d", &key); root = insert(root, key); break;
            case 2: preorder(root); break;
            case 3: postorder(root); break;
            case 4: printf("Total nodes: %d\n", countNodes(root)); break;
            case 5: printLeafNodes(root); break;
            case 6: return 0;
            default: printf("Invalid!\n");
        }
    }
}

