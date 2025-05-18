#include <stdio.h>
#define SIZE 5

int deque[SIZE], front = -1, rear = -1;

int isFull()  { return (front == (rear + 1) % SIZE); }
int isEmpty() { return (front == -1); }

void insert(int val, int atFront) {
    if (isFull()) { printf("Queue is Full!\n"); return; }

    if (isEmpty()) front = rear = 0;
    else if (atFront) front = (front - 1 + SIZE) % SIZE;
    else rear = (rear + 1) % SIZE;

    deque[atFront ? front : rear] = val;
}

void delete(int fromFront) {
    if (isEmpty()) { printf("Queue is Empty!\n"); return; }

    if (front == rear) front = rear = -1;
    else if (fromFront) front = (front + 1) % SIZE;
    else rear = (rear - 1 + SIZE) % SIZE;
}

void display() {
    if (isEmpty()) { printf("Queue is Empty!\n"); return; }
    printf("Queue: ");
    for (int i = front; ; i = (i + 1) % SIZE) {
        printf("%d ", deque[i]);
        if (i == rear) break;
    }
    printf("\n");
}

int main() {
    int ch, val;
    while (1) {
        printf("\n1.InsertFront 2.InsertRear 3.DeleteFront 4.DeleteRear 5.Display 6.Exit\nChoose: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: case 2:
                printf("Value: "); scanf("%d", &val);
                insert(val, ch == 1);
                break;
            case 3: case 4:
                delete(ch == 3);
                break;
            case 5: display(); break;
            case 6: return 0;
            default: printf("Invalid choice!\n");
        }
    }
}
