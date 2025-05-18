#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

// Queue for level order traversal
typedef struct Queue {
    Node* data[100];
    int front, rear;
} Queue;

void initQueue(Queue* q) {
    q->front = q->rear = 0;
}

void enqueue(Queue* q, Node* node) {
    q->data[q->rear++] = node;
}

Node* dequeue(Queue* q) {
    return q->data[q->front++];
}

int isEmpty(Queue* q) {
    return q->front == q->rear;
}

// Create a new BST node
Node* createNode(int key) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->key = key;
    n->left = n->right = NULL;
    return n;
}

// Recursive insert
Node* insert(Node* root, int key) {
    if (!root) return createNode(key);
    if (key < root->key)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);
    return root;
}

// Find min node (used for delete)
Node* findMin(Node* root) {
    while (root && root->left)
        root = root->left;
    return root;
}

// Recursive delete
Node* deleteNode(Node* root, int key) {
    if (!root) return NULL;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        if (!root->right) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = findMin(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

// Level-wise display, each level in new line
void levelOrderLineByLine(Node* root) {
    if (!root) {
        printf("Tree is empty.\n");
        return;
    }

    Queue q;
    initQueue(&q);
    enqueue(&q, root);
    enqueue(&q, NULL); // Level marker

    while (!isEmpty(&q)) {
        Node* curr = dequeue(&q);

        if (curr == NULL) {
            printf("\n");
            if (!isEmpty(&q))
                enqueue(&q, NULL);
        } else {
            printf("%d ", curr->key);
            if (curr->left)
                enqueue(&q, curr->left);
            if (curr->right)
                enqueue(&q, curr->right);
        }
    }
}

// MAIN
int main() {
    Node* root = NULL;
    int ch, key;

    while (1) {
        printf("\n1.Insert  2.Delete  3.Levelwise Display (Line by Line)  4.Exit\nEnter choice: ");
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
                printf("Levelwise display (each level on new line):\n");
                levelOrderLineByLine(root);
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}
