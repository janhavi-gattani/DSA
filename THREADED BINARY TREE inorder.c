#include <stdio.h>
#include <stdlib.h>

// Node structure for Inorder Threaded Binary Tree
typedef struct Node {
    int data;
    struct Node *left, *right;
    int lthread, rthread; // 1 if thread, 0 if child
} Node;

// Create a new node (threaded)
Node* createNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->left = temp->right = NULL;
    temp->lthread = temp->rthread = 1; // Initially threads
    return temp;
}

// Insert node in BST and maintain inorder threads
Node* insert(Node* root, int key) {
    if (root == NULL)
        return createNode(key);

    Node* curr = root;
    Node* parent = NULL;

    while (curr != NULL) {
        if (key == curr->data) {
            printf("Duplicate key %d not allowed.\n", key);
            return root;
        }
        parent = curr;
        if (key < curr->data) {
            if (curr->lthread == 0)
                curr = curr->left;
            else
                break;
        } else {
            if (curr->rthread == 0)
                curr = curr->right;
            else
                break;
        }
    }

    Node* newNode = createNode(key);

    if (key < parent->data) {
        newNode->left = parent->left;
        newNode->right = parent;
        parent->lthread = 0;
        parent->left = newNode;
    } else {
        newNode->right = parent->right;
        newNode->left = parent;
        parent->rthread = 0;
        parent->right = newNode;
    }
    return root;
}

// Find leftmost node (starting point for inorder traversal)
Node* leftMost(Node* node) {
    if (node == NULL)
        return NULL;
    while (node->lthread == 0)
        node = node->left;
    return node;
}

// Inorder traversal using threads
void inorder(Node* root) {
    if (root == NULL) return;

    Node* curr = leftMost(root);

    while (curr != NULL) {
        printf("%d ", curr->data);

        // If right thread exists, follow it
        if (curr->rthread == 1)
            curr = curr->right;
        else
            // Else go to the leftmost node in right subtree
            curr = leftMost(curr->right);
    }
}

int main() {
    Node* root = NULL;
    int n, val;

    printf("How many nodes you want to insert? ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter node %d value: ", i + 1);
        scanf("%d", &val);
        root = insert(root, val);
    }

    printf("Inorder traversal of Inorder Threaded Binary Tree:\n");
    inorder(root);

    return 0;
}
