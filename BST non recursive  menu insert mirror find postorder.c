#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Node structure
typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

// Create a new node
Node* createNode(int key) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->key = key;
    temp->left = temp->right = NULL;
    return temp;
}

// Non-recursive Insert
Node* insert(Node* root, int key) {
    Node* newnode = createNode(key);
    if (root == NULL) return newnode;

    Node* parent = NULL;
    Node* curr = root;

    while (curr != NULL) {
        parent = curr;
        if (key < curr->key)
            curr = curr->left;
        else if (key > curr->key)
            curr = curr->right;
        else {
            printf("Key %d already exists!\n", key);
            free(newnode);
            return root;
        }
    }

    if (key < parent->key)
        parent->left = newnode;
    else
        parent->right = newnode;

    return root;
}

// Non-recursive Find
int find(Node* root, int key) {
    while (root != NULL) {
        if (key == root->key)
            return 1;
        else if (key < root->key)
            root = root->left;
        else
            root = root->right;
    }
    return 0;
}

// Non-recursive Mirror using stack
void mirrorImage(Node* root) {
    if (root == NULL) return;

    Node* stack[MAX];
    int top = -1;
    stack[++top] = root;

    while (top >= 0) {
        Node* curr = stack[top--];

        // Swap children
        Node* temp = curr->left;
        curr->left = curr->right;
        curr->right = temp;

        if (curr->left)
            stack[++top] = curr->left;
        if (curr->right)
            stack[++top] = curr->right;
    }

    printf("Mirror image created successfully.\n");
}

// Non-recursive Postorder using 2 stacks
void postorder(Node* root) {
    if (!root) return;

    Node* s1[MAX], *s2[MAX];
    int top1 = -1, top2 = -1;

    s1[++top1] = root;

    while (top1 >= 0) {
        Node* node = s1[top1--];
        s2[++top2] = node;

        if (node->left) s1[++top1] = node->left;
        if (node->right) s1[++top1] = node->right;
    }

    printf("Postorder traversal: ");
    while (top2 >= 0) {
        printf("%d ", s2[top2--]->key);
    }
    printf("\n");
}

// Main menu
int main() {
    Node* root = NULL;
    int choice, key;

    while (1) {
        printf("\n--- BST Non-Recursive Operations Menu ---\n");
        printf("1. Insert\n2. Mirror Image\n3. Find\n4. Postorder\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;

            case 2:
                mirrorImage(root);
                break;

            case 3:
                printf("Enter key to find: ");
                scanf("%d", &key);
                if (find(root, key))
                    printf("Key %d found in BST.\n", key);
                else
                    printf("Key %d NOT found in BST.\n", key);
                break;

            case 4:
                postorder(root);
                break;

            case 5:
                printf("Exiting program.\n");
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
