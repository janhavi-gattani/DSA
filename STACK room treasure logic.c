#include <stdio.h>
#define MAX 100

// Stack structure
typedef struct {
    int arr[MAX];
    int top;
} Stack;

// Initialize stack
void init(Stack *s) {
    s->top = -1;
}

// Check if stack is empty
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Push element to stack
void push(Stack *s, int val) {
    if (s->top < MAX - 1) {
        s->arr[++(s->top)] = val;
    }
}

// Pop element from stack
int pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->arr[(s->top)--];
    }
    return -1; // Error code for empty stack
}

// Convert decimal to binary using stack
void decimalToBinary(int num, Stack *binaryStack) {
    if (num == 0) {
        push(binaryStack, 0);
    }
    while (num > 0) {
        push(binaryStack, num % 2);
        num = num / 2;
    }
}

int main() {
    Stack roomStack;
    Stack binaryStack;
    int room;

    init(&roomStack);
    init(&binaryStack);

    // Moving from room 1 to 5
    printf("Moving from Room 1 to Room 5:\n");
    for (room = 1; room <= 5; room++) {
        printf("Entered Room %d\n", room);
        push(&roomStack, room);
    }

    // In room 5, read the decimal number
    int decimalNumber;
    printf("Enter the decimal number found in Room 5 box: ");
    scanf("%d", &decimalNumber);

    // Convert decimal to binary using stack
    decimalToBinary(decimalNumber, &binaryStack);

    // Moving back from room 5 to room 1
    printf("\nMoving back from Room 5 to Room 1:\n");
    while (!isEmpty(&roomStack)) {
        int currentRoom = pop(&roomStack);
        printf("Exited Room %d\n", currentRoom);
        if (currentRoom == 1) {
            printf("\nReached Room 1, treasure room.\n");
            printf("Binary code to unlock treasure: ");
            while (!isEmpty(&binaryStack)) {
                printf("%d", pop(&binaryStack));
            }
            printf("\n");
        }
    }

    return 0;
}
