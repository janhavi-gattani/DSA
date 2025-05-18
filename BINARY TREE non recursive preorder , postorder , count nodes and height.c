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

// Preorder traversal (non-recursive)
void preorder(Node *root) {
    Stack s; s.top = -1;
    if (!root) return;
    push(&s, root);
    printf("Preorder: ");
    while (!isStackEmpty(&s)) {
        Node *curr = pop(&s);
        printf("%d ", curr->data);
        if (curr->right) push(&s, curr->right);
        if (curr->left) push(&s, curr->left);
    }
    printf("\n");
}

// Postorder traversal (non-recursive)
void postorder(Node *root) {
    Stack s1, s2;
    s1.top = s2.top = -1;
    if (!root) return;
    push(&s1, root);
    while (!isStackEmpty(&s1)) {
        Node *curr = pop(&s1);
        push(&s2, curr);
        if (curr->left) push(&s1, curr->left);
        if (curr->right) push(&s1, curr->right);
    }
    printf("Postorder: ");
    while (!isStackEmpty(&s2)) {
        printf("%d ", pop(&s2)->data);
    }
    printf("\n");
}

// Count nodes (non-recursive)
int countNodes(Node *root) {
    if (!root) return 0;
    Stack s; s.top = -1;
    int count = 0;
    push(&s, root);
    while (!isStackEmpty(&s)) {
        Node *curr = pop(&s);
        count++;
        if (curr->left) push(&s, curr->left);
        if (curr->right) push(&s, curr->right);
    }
    return count;
}

// Height of tree (non-recursive, level order)
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

int main() {
    Node *root = buildTree();
    preorder(root);
    postorder(root);
    printf("Total nodes: %d\n", countNodes(root));
    printf("Height of tree: %d\n", height(root));
    return 0;
}
