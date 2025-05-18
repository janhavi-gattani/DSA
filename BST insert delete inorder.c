#include <stdio.h>
#include <stdlib.h>

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

// Insert key in BST
Node* insert(Node* root, int key) {
    if (!root) return newNode(key);
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        printf("Key %d already exists!\n", key);
    return root;
}

// Find minimum value node in BST (used in delete)
Node* minValueNode(Node* root) {
    Node* current = root;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Delete key from BST
Node* deleteNode(Node* root, int key) {
    if (!root) {
        printf("Key %d not found.\n", key);
        return root;
    }

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // node with one or no child
        if (!root->left) {
            Node* temp = root->right;
            free(root);
            printf("Deleted key %d.\n", key);
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            free(root);
            printf("Deleted key %d.\n", key);
            return temp;
        }

        // node with two children: get inorder successor (min in right subtree)
        Node* temp = minValueNode(root->right);
        root->key = temp->key;  // copy inorder successor's key
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

// Find a key
int find(Node* root, int key) {
    if (!root) return 0;
    if (key == root->key) return 1;
    if (key < root->key) return find(root->left, key);
    return find(root->right, key);
}

// Inorder display (sorted)
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

int main() {
    Node* root = NULL;
    int choice, key;

    while (1) {
        printf("\n--- BST Operations Menu ---\n");
        printf("1. Insert\n2. Delete\n3. Find\n4. Display Inorder\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;

            case 2:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                root = deleteNode(root, key);
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
                printf("BST Inorder: ");
                inorder(root);
                printf("\n");
                break;

            case 5:
                printf("Exiting program.\n");
                exit(0);

            default:
                printf("Invalid choice, try again.\n");
        }
    }

    return 0;
}
