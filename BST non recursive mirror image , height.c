#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

// Queue for BFS (used for mirror and height)
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

// Stack for copy
typedef struct Stack {
    Node* data[100];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

void push(Stack* s, Node* node) {
    s->data[++s->top] = node;
}

Node* pop(Stack* s) {
    return s->data[s->top--];
}

int isStackEmpty(Stack* s) {
    return s->top == -1;
}

// Create new node
Node* createNode(int key) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->key = key;
    n->left = n->right = NULL;
    return n;
}

// Insert into BST (non-recursive)
Node* insert(Node* root, int key) {
    Node* newNode = createNode(key);
    if (!root) return newNode;

    Node* current = root;
    Node* parent = NULL;

    while (current) {
        parent = current;
        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }

    if (key < parent->key)
        parent->left = newNode;
    else
        parent->right = newNode;

    return root;
}

// Inorder traversal (non-recursive)
void inorder(Node* root) {
    Stack s;
    initStack(&s);
    Node* curr = root;

    while (curr || !isStackEmpty(&s)) {
        while (curr) {
            push(&s, curr);
            curr = curr->left;
        }
        curr = pop(&s);
        printf("%d ", curr->key);
        curr = curr->right;
    }
}

// Height of tree (non-recursive)
int getHeight(Node* root) {
    if (!root) return 0;

    Queue q;
    initQueue(&q);
    enqueue(&q, root);
    int height = 0;

    while (1) {
        int nodeCount = q.rear - q.front;
        if (nodeCount == 0)
            return height;
        height++;

        while (nodeCount > 0) {
            Node* node = dequeue(&q);
            if (node->left) enqueue(&q, node->left);
            if (node->right) enqueue(&q, node->right);
            nodeCount--;
        }
    }
}

// Mirror the tree (non-recursive)
void mirror(Node* root) {
    if (!root) return;

    Queue q;
    initQueue(&q);
    enqueue(&q, root);

    while (!isEmpty(&q)) {
        Node* node = dequeue(&q);
        Node* temp = node->left;
        node->left = node->right;
        node->right = temp;

        if (node->left) enqueue(&q, node->left);
        if (node->right) enqueue(&q, node->right);
    }
}

// Copy tree (non-recursive, returns new root)
Node* copyTree(Node* root) {
    if (!root) return NULL;

    Queue q1, q2;
    initQueue(&q1);
    initQueue(&q2);

    Node* newRoot = createNode(root->key);
    enqueue(&q1, root);
    enqueue(&q2, newRoot);

    while (!isEmpty(&q1)) {
        Node* orig = dequeue(&q1);
        Node* copy = dequeue(&q2);

        if (orig->left) {
            copy->left = createNode(orig->left->key);
            enqueue(&q1, orig->left);
            enqueue(&q2, copy->left);
        }
        if (orig->right) {
            copy->right = createNode(orig->right->key);
            enqueue(&q1, orig->right);
            enqueue(&q2, copy->right);
        }
    }

    return newRoot;
}

// MAIN
int main() {
    Node* root = NULL;
    int choice, key;

    while (1) {
        printf("\n1.Insert\n2.Inorder Display\n3.Mirror Original\n4.Mirror Copy (without disturbing original)\n5.Height of Tree\n6.Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;

            case 2:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;

            case 3:
                mirror(root);
                printf("Original tree mirrored.\n");
                break;

            case 4: {
                Node* copy = copyTree(root);
                mirror(copy);
                printf("Inorder of mirrored copy: ");
                inorder(copy);
                printf("\nOriginal tree remains: ");
                inorder(root);
                printf("\n");
                break;
            }

            case 5:
                printf("Height of tree = %d\n", getHeight(root));
                break;

            case 6:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
