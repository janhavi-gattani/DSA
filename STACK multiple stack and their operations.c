#include <stdio.h>
#define MAX 100

int arr[MAX];      // Common array to hold all stacks
int top[10];       // Array to track top of each stack
int base[10];      // Array to track base(start index) of each stack
int size, n;       // size = size of each stack, n = number of stacks

// Initialize stacks
void init() {
    printf("Enter number of stacks (max 10): ");
    scanf("%d", &n);
    printf("Enter size of each stack: ");
    scanf("%d", &size);

    for (int i = 0; i < n; i++) {
        base[i] = i * size;
        top[i] = base[i] - 1;
    }
}

// Check if stack is full
int isFull(int sn) {
    return top[sn] == base[sn] + size - 1;
}

// Check if stack is empty
int isEmpty(int sn) {
    return top[sn] < base[sn];
}

// PUSH operation
void push(int sn, int val) {
    if (isFull(sn))
        printf("Stack %d is Full!\n", sn);
    else {
        top[sn]++;
        arr[top[sn]] = val;
        printf("Pushed %d into Stack %d\n", val, sn);
    }
}

// POP operation
void pop(int sn) {
    if (isEmpty(sn))
        printf("Stack %d is Empty!\n", sn);
    else {
        int val = arr[top[sn]];
        top[sn]--;
        printf("Popped %d from Stack %d\n", val, sn);
    }
}

// Display contents of a stack
void display(int sn) {
    if (isEmpty(sn)) {
        printf("Stack %d is Empty!\n", sn);
    } else {
        printf("Stack %d: ", sn);
        for (int i = base[sn]; i <= top[sn]; i++)
            printf("%d ", arr[i]);
        printf("\n");
    }
}

// Check stack full status
void checkFull(int sn) {
    if (isFull(sn))
        printf("Stack %d is FULL.\n", sn);
    else
        printf("Stack %d is NOT full.\n", sn);
}

// Check stack empty status
void checkEmpty(int sn) {
    if (isEmpty(sn))
        printf("Stack %d is EMPTY.\n", sn);
    else
        printf("Stack %d is NOT empty.\n", sn);
}

int main() {
    init();
    int choice, sn, val;

    while (1) {
        printf("\n=== MENU ===\n");
        printf("1. PUSH\n2. POP\n3. Check Stack FULL\n4. Check Stack EMPTY\n5. Display Stack\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 6) break;

        printf("Enter stack number (0 to %d): ", n - 1);
        scanf("%d", &sn);

        if (sn < 0 || sn >= n) {
            printf("Invalid stack number!\n");
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter value to PUSH: ");
                scanf("%d", &val);
                push(sn, val);
                break;
            case 2:
                pop(sn);
                break;
            case 3:
                checkFull(sn);
                break;
            case 4:
                checkEmpty(sn);
                break;
            case 5:
                display(sn);
                break;
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
