#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;

// Create new node
Node* newNode(int key) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->key = key;
    n->left = n->right = NULL;
    return n;
}

// Insert key in BST (recursive for simplicity)
Node* insert(Node* root, int key) {
    if (!root) return newNode(key);
    if (key < root->key) root->left = insert(root->left, key);
    else if (key > root->key) root->right = insert(root->right, key);
    return root;
}

// Level-wise display using simple array queue
void levelDisplay(Node* root) {
    if (!root) {
        printf("Tree is empty\n");
        return;
    }

    Node* queue[MAX];
    int front = 0, rear = 0;
    queue[rear++] = root;

    printf("Level-wise: ");
    while (front < rear) {
        Node* curr = queue[front++];
        printf("%d ", curr->key);

        if (curr->left) queue[rear++] = curr->left;
        if (curr->right) queue[rear++] = curr->right;
    }
    printf("\n");
}

// Mirror image using stack with array
void mirror(Node* root) {
    if (!root) return;

    Node* stack[MAX];
    int top = -1;
    stack[++top] = root;

    while (top >= 0) {
        Node* curr = stack[top--];

        // Swap children
        Node* temp = curr->left;
        curr->left = curr->right;
        curr->right = temp;

        if (curr->left) stack[++top] = curr->left;
        if (curr->right) stack[++top] = curr->right;
    }
}

// Height calculation using level-wise traversal (BFS)
int height(Node* root) {
    if (!root) return 0;

    Node* queue[MAX];
    int front = 0, rear = 0;
    queue[rear++] = root;
    int height = 0;

    while (1) {
        int count = rear - front;
        if (count == 0) break;
        height++;

        while (count--) {
            Node* curr = queue[front++];
            if (curr->left) queue[rear++] = curr->left;
            if (curr->right) queue[rear++] = curr->right;
        }
    }
    return height;
}

int main() {
    Node* root = NULL;
    int n, key;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter %d keys:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &key);
        root = insert(root, key);
    }

    levelDisplay(root);

    printf("Height of tree: %d\n", height(root));

    mirror(root);

    printf("After mirror image:\n");
    levelDisplay(root);

    return 0;
}
