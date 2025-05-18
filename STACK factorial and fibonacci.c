#include <stdio.h>
#define MAX 100

typedef struct {
    int arr[MAX];
    int top;
} Stack;

// Stack functions
void init(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, int val) {
    if (!isFull(s)) {
        s->arr[++(s->top)] = val;
    }
}

int pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->arr[(s->top)--];
    }
    return -1; // error code
}

// A. Factorial using stack
int factorial(int n) {
    Stack s;
    init(&s);

    // Push all numbers from n down to 1 on the stack
    for (int i = n; i > 0; i--) {
        push(&s, i);
    }

    int result = 1;
    // Pop and multiply all numbers
    while (!isEmpty(&s)) {
        result *= pop(&s);
    }
    return result;
}

// B. Fibonacci series using stack
void fibonacci(int terms) {
    Stack s;
    init(&s);

    int a = 0, b = 1, next;

    printf("Fibonacci Series: ");

    for (int i = 1; i <= terms; i++) {
        if (i == 1) {
            printf("%d ", a);
            push(&s, a);
        } else if (i == 2) {
            printf("%d ", b);
            push(&s, b);
        } else {
            next = a + b;
            printf("%d ", next);
            push(&s, next);
            a = b;
            b = next;
        }
    }
    printf("\n");

    // Optionally, show stack content (fibonacci numbers stored)
    printf("Fibonacci numbers in stack (top to bottom): ");
    while (!isEmpty(&s)) {
        printf("%d ", pop(&s));
    }
    printf("\n");
}

int main() {
    int choice, n;

    printf("Choose:\n1. Factorial\n2. Fibonacci Series\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter a number to find factorial: ");
        scanf("%d", &n);
        if (n < 0) {
            printf("Factorial not defined for negative numbers.\n");
        } else {
            printf("Factorial of %d is %d\n", n, factorial(n));
        }
    } else if (choice == 2) {
        printf("Enter the number of terms for Fibonacci series: ");
        scanf("%d", &n);
        if (n <= 0) {
            printf("Enter a positive integer.\n");
        } else {
            fibonacci(n);
        }
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
