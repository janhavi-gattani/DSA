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

// Non-recursive insert into BST
Node* insert(Node* root, int key) {
    Node* newNode = createNode(key);
    if (root == NULL) return newNode;

    Node *curr = root, *parent = NULL;

    while (curr != NULL) {
        parent = curr;
        if (key < curr->key)
            curr = curr->left;
        else if (key > curr->key)
            curr = curr->right;
        else {
            printf("Key already exists!\n");
            free(newNode);
            return root;
        }
    }

    if (key < parent->key)
        parent->left = newNode;
    else
        parent->right = newNode;

    return root;
}

// Non-recursive Inorder traversal
void inorder(Node* root) {
    Node* stack[MAX];
    int top = -1;
    Node* curr = root;

    printf("Inorder: ");
    while (curr != NULL || top != -1) {
        while (curr != NULL) {
            stack[++top] = curr;
            curr = curr->left;
        }
        curr = stack[top--];
        printf("%d ", curr->key);
        curr = curr->right;
    }
    printf("\n");
}

// Non-recursive Preorder traversal
void preorder(Node* root) {
    if (root == NULL) return;

    Node* stack[MAX];
    int top = -1;
    stack[++top] = root;

    printf("Preorder: ");
    while (top != -1) {
        Node* curr = stack[top--];
        printf("%d ", curr->key);

        if (curr->right)
            stack[++top] = curr->right;
        if (curr->left)
            stack[++top] = curr->left;
    }
    printf("\n");
}

// Non-recursive count of leaf nodes
int countLeafNodes(Node* root) {
    if (root == NULL) return 0;

    Node* stack[MAX];
    int top = -1, count = 0;
    stack[++top] = root;

    while (top != -1) {
        Node* curr = stack[top--];
        if (curr->left == NULL && curr->right == NULL)
            count++;

        if (curr->right)
            stack[++top] = curr->right;
        if (curr->left)
            stack[++top] = curr->left;
    }
    return count;
}

// Non-recursive mirror image
void mirrorImage(Node* root) {
    if (root == NULL) return;

    Node* stack[MAX];
    int top = -1;
    stack[++top] = root;

    while (top != -1) {
        Node* curr = stack[top--];

        // Swap left and right
        Node* temp = curr->left;
        curr->left = curr->right;
        curr->right = temp;

        if (curr->left) stack[++top] = curr->left;
        if (curr->right) stack[++top] = curr->right;
    }

    printf("Mirror image created.\n");
}

// Main menu
int main() {
    Node* root = NULL;
    int choice, key;

    while (1) {
        printf("\n--- BST Non-Recursive Operations Menu ---\n");
        printf("1. Insert\n2. Preorder Traversal\n3. Inorder Traversal\n4. Count Leaf Nodes\n5. Mirror Image\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;

            case 2:
                preorder(root);
                break;

            case 3:
                inorder(root);
                break;

            case 4:
                printf("Number of leaf nodes: %d\n", countLeafNodes(root));
                break;

            case 5:
                mirrorImage(root);
                break;

            case 6:
                printf("Exiting program.\n");
                exit(0);

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
