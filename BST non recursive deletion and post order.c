#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

// Create a new node
Node* createNode(int key) {
    Node* n = malloc(sizeof(Node));
    n->key = key;
    n->left = n->right = NULL;
    return n;
}

// Insert (non-recursive)
Node* insert(Node* root, int key) {
    Node *curr = root, *parent = NULL;
    Node* n = createNode(key);
    if (!root) return n;

    while (curr) {
        parent = curr;
        if (key < curr->key) curr = curr->left;
        else curr = curr->right;
    }
    if (key < parent->key) parent->left = n;
    else parent->right = n;
    return root;
}

// Find minimum node (used for replacing in two-child case)
Node* findMin(Node* node) {
    while (node && node->left) node = node->left;
    return node;
}

// Delete node (non-recursive)
Node* deleteNode(Node* root, int key) {
    Node *curr = root, *parent = NULL;

    // Search for node and parent
    while (curr && curr->key != key) {
        parent = curr;
        if (key < curr->key) curr = curr->left;
        else curr = curr->right;
    }
    if (!curr) {
        printf("Key not found.\n");
        return root;
    }

    // Case 1 & 2: Node with 0 or 1 child
    if (!curr->left || !curr->right) {
        Node* child = curr->left ? curr->left : curr->right;
        if (!parent) return child; // Deleting root
        if (parent->left == curr) parent->left = child;
        else parent->right = child;
        free(curr);
    }
    // Case 3: Node with 2 children
    else {
        Node *succParent = curr, *succ = curr->right;
        while (succ->left) {
            succParent = succ;
            succ = succ->left;
        }
        curr->key = succ->key;  // Replace
        // Delete successor
        if (succParent->left == succ)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;
        free(succ);
    }

    return root;
}

// Non-recursive postorder using 2 stacks
void postorder(Node* root) {
    if (!root) return;
    Node *s1[MAX], *s2[MAX];
    int top1 = -1, top2 = -1;
    s1[++top1] = root;

    while (top1 != -1) {
        Node* n = s1[top1--];
        s2[++top2] = n;
        if (n->left) s1[++top1] = n->left;
        if (n->right) s1[++top1] = n->right;
    }

    printf("Postorder: ");
    while (top2 != -1) printf("%d ", s2[top2--]->key);
    printf("\n");
}

// Non-recursive inorder display
void inorder(Node* root) {
    Node* stack[MAX];
    int top = -1;
    Node* curr = root;
    printf("Inorder (sorted): ");
    while (curr || top != -1) {
        while (curr) {
            stack[++top] = curr;
            curr = curr->left;
        }
        curr = stack[top--];
        printf("%d ", curr->key);
        curr = curr->right;
    }
    printf("\n");
}

// Main menu
int main() {
    Node* root = NULL;
    int ch, key;

    while (1) {
        printf("\n1.Insert 2.Delete 3.Postorder 4.Display(Inorder) 5.Exit\nEnter choice: ");
        scanf("%d", &ch);
        switch (ch) {
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
                postorder(root);
                break;
            case 4:
                inorder(root);
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}
