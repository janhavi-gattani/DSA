#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

typedef struct Queue {
    Node *arr[100];
    int front, rear;
} Queue;

void enqueue(Queue *q, Node *node) {
    q->arr[q->rear++] = node;
}
Node* dequeue(Queue *q) {
    if (q->front == q->rear) return NULL;
    return q->arr[q->front++];
}
int isEmpty(Queue *q) {
    return q->front == q->rear;
}

typedef struct Stack {
    Node *arr[100];
    int top;
} Stack;

void push(Stack *s, Node *node) {
    s->arr[++s->top] = node;
}
Node* pop(Stack *s) {
    return s->top == -1 ? NULL : s->arr[s->top--];
}
int isStackEmpty(Stack *s) {
    return s->top == -1;
}

Node* newNode(int val) {
    Node *temp = malloc(sizeof(Node));
    temp->data = val;
    temp->left = temp->right = NULL;
    return temp;
}

// Build tree from user input (level order)
Node* buildTree() {
    int val;
    printf("Enter root node value: ");
    scanf("%d", &val);
    if (val == -1) return NULL;

    Node *root = newNode(val);
    Queue q = {.front = 0, .rear = 0};
    enqueue(&q, root);

    while (!isEmpty(&q)) {
        Node *curr = dequeue(&q);

        printf("Enter left child of %d (-1 for no child): ", curr->data);
        scanf("%d", &val);
        if (val != -1) {
            curr->left = newNode(val);
            enqueue(&q, curr->left);
        }

        printf("Enter right child of %d (-1 for no child): ", curr->data);
        scanf("%d", &val);
        if (val != -1) {
            curr->right = newNode(val);
            enqueue(&q, curr->right);
        }
    }
    return root;
}

// Non-recursive inorder traversal using stack
void inorder(Node *root) {
    Stack s; s.top = -1;
    Node *curr = root;
    printf("Inorder: ");
    while (curr != NULL || !isStackEmpty(&s)) {
        while (curr != NULL) {
            push(&s, curr);
            curr = curr->left;
        }
        curr = pop(&s);
        printf("%d ", curr->data);
        curr = curr->right;
    }
    printf("\n");
}

// Count number of nodes on longest path (which is height of tree)
int height(Node *root) {
    if (!root) return 0;
    Node *queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;
    int h = 0;
    while (front < rear) {
        int size = rear - front;
        h++;
        for (int i = 0; i < size; i++) {
            Node *curr = queue[front++];
            if (curr->left) queue[rear++] = curr->left;
            if (curr->right) queue[rear++] = curr->right;
        }
    }
    return h;
}

// Display tree levelwise (level order traversal)
void levelOrder(Node *root) {
    if (!root) return;
    Queue q = {.front = 0, .rear = 0};
    enqueue(&q, root);
    printf("Level-wise: ");
    while (!isEmpty(&q)) {
        Node *curr = dequeue(&q);
        printf("%d ", curr->data);
        if (curr->left) enqueue(&q, curr->left);
        if (curr->right) enqueue(&q, curr->right);
    }
    printf("\n");
}

int main() {
    Node *root = buildTree();

    inorder(root);
    printf("Number of nodes on longest path: %d\n", height(root));
    levelOrder(root);
    printf("Height of tree: %d\n", height(root));

    return 0;
}
