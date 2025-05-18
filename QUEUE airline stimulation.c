#include <stdio.h>
#define MAX 100

int ffQueue[MAX], rQueue[MAX];
int ffFront = 0, ffRear = 0, rFront = 0, rRear = 0;
int time = 0, ffWait = 0, rWait = 0, ffCount = 0, rCount = 0;

// Add passenger to queue
void enqueue(int queue[], int *rear, int arrival) {
    queue[(*rear)++] = arrival;
}

// Remove passenger from queue
int dequeue(int queue[], int *front) {
    return queue[(*front)++];
}

int isEmpty(int front, int rear) {
    return front == rear;
}

// Simulate the ticket counter
void simulate() {
    while (!isEmpty(ffFront, ffRear) || !isEmpty(rFront, rRear)) {
        if (!isEmpty(ffFront, ffRear)) {
            int arrival = dequeue(ffQueue, &ffFront);
            ffWait += time - arrival;
            time++; ffCount++;
        } else if (!isEmpty(rFront, rRear)) {
            int arrival = dequeue(rQueue, &rFront);
            rWait += time - arrival;
            time++; rCount++;
        } else {
            time++; // wait for next arrival
        }
    }
    printf("\nAverage wait (Frequent Flyers): %.2f", ffCount ? (float)ffWait / ffCount : 0);
    printf("\nAverage wait (Regular Customers): %.2f\n", rCount ? (float)rWait / rCount : 0);
}

int main() {
    int n, type, arrival;
    printf("Enter number of passengers: ");
    scanf("%d", &n);
    printf("Enter details (0=Regular, 1=Frequent Flyer)\n");
    for (int i = 0; i < n; i++) {
        printf("Passenger %d - Type and Arrival Time: ", i + 1);
        scanf("%d %d", &type, &arrival);
        if (type == 1)
            enqueue(ffQueue, &ffRear, arrival);
        else
            enqueue(rQueue, &rRear, arrival);
    }
    simulate();
    return 0;
}
