#include <stdio.h>
#define SIZE 5

int queue1[SIZE], front1 = -1, rear1 = -1;
int queue2[SIZE], front2 = -1, rear2 = -1;

// Add element to queue
void addq(int queue[], int *front, int *rear, int value) {
    if (*rear == SIZE - 1) {
        printf("Queue is Full!\n");
        return;
    }
    if (*front == -1)
        *front = 0;
    (*rear)++;
    queue[*rear] = value;
    printf("Added %d to queue.\n", value);
}

// Delete element from queue
void delq(int queue[], int *front, int *rear) {
    if (*front == -1 || *front > *rear) {
        printf("Queue is Empty!\n");
        return;
    }
    printf("Deleted %d from queue.\n", queue[*front]);
    (*front)++;
    if (*front > *rear) // reset after last element is deleted
        *front = *rear = -1;
}

// Display queue contents
void display(int queue[], int front, int rear) {
    if (front == -1 || front > rear) {
        printf("Queue is Empty!\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = front; i <= rear; i++)
        printf("%d ", queue[i]);
    printf("\n");
}

int main() {
    int choice, qNum, val;

    while (1) {
        printf("\n1.Addq  2.Delq  3.Display  4.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4) break;

        printf("Select Queue (1 or 2): ");
        scanf("%d", &qNum);

        switch (choice) {
            case 1:
                printf("Enter value to add: ");
                scanf("%d", &val);
                if (qNum == 1)
                    addq(queue1, &front1, &rear1, val);
                else
                    addq(queue2, &front2, &rear2, val);
                break;

            case 2:
                if (qNum == 1)
                    delq(queue1, &front1, &rear1);
                else
                    delq(queue2, &front2, &rear2);
                break;

            case 3:
                if (qNum == 1)
                    display(queue1, front1, rear1);
                else
                    display(queue2, front2, rear2);
                break;

            default:
                printf("Invalid Choice!\n");
        }
    }

    return 0;
}
