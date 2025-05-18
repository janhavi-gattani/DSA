#include <stdio.h>
#include <stdlib.h>

// AVL Tree Node
typedef struct Node {
    int key;
    int height;
    struct Node* left;
    struct Node* right;
} Node;

// Helper functions
int height(Node* node) {
    return node ? node->height : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

int getBalance(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Rotations
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

// Insert function
Node* insert(Node* root, int key) {
    if (!root)
        return createNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root;  // no duplicates

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    // Balancing
    if (balance > 1 && key < root->left->key)
        return rightRotate(root);          // LL
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);           // RR
    if (balance > 1 && key > root->left->key) { // LR
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && key < root->right->key) { // RL
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Find minimum node in subtree
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left)
        current = current->left;
    return current;
}

// Delete function
Node* deleteNode(Node* root, int key) {
    if (!root) return NULL;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Found node to be deleted
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // Update height
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    // Rebalance
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);              // LL
    if (balance > 1 && getBalance(root->left) < 0) { // LR
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);               // RR
    if (balance < -1 && getBalance(root->right) > 0) { // RL
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Search function
int search(Node* root, int key) {
    if (!root)
        return 0;
    if (key == root->key)
        return 1;
    if (key < root->key)
        return search(root->left, key);
    return search(root->right, key);
}

// Level-order display
void levelOrder(Node* root) {
    if (!root) return;

    Node* queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        int count = rear - front;

        for (int i = 0; i < count; i++) {
            Node* curr = queue[front++];
            printf("%d ", curr->key);
            if (curr->left)
                queue[rear++] = curr->left;
            if (curr->right)
                queue[rear++] = curr->right;
        }
        printf("\n");
    }
}

// Free memory
void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Main Menu
int main() {
    Node* root = NULL;
    int choice, val;

    printf("====== AVL Tree Menu ======\n");
    while (1) {
        printf("\n1. Insert\n2. Delete\n3. Search\n4. Display Level-wise\n5. Exit\nChoose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                root = insert(root, val);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &val);
                root = deleteNode(root, val);
                break;
            case 3:
                printf("Enter value to search: ");
                scanf("%d", &val);
                if (search(root, val))
                    printf("Found!\n");
                else
                    printf("Not found!\n");
                break;
            case 4:
                printf("Level-wise AVL Tree:\n");
                levelOrder(root);
                break;
            case 5:
                freeTree(root);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}
