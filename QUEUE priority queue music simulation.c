#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
typedef struct {
char name[50];
int priority; // 1: Download, 2: Music, 3: Game
} Task;
typedef struct {
Task tasks[MAX];
int front, rear;
} Queue;
void initQueue(Queue *q) {
q->front = q->rear = -1;
}
int isEmpty(Queue *q) {
return q->front == -1;
}
int isFull(Queue *q) {
return q->rear == MAX - 1;
}
void enqueue(Queue *q, Task t) {
if (isFull(q)) {
printf("Queue is full!\n");
return;
}
if (isEmpty(q)) {
q->front = q->rear = 0;
} else {
q->rear++;
}
q->tasks[q->rear] = t;
}
Task dequeue(Queue *q) {
Task t = {"", -1};
if (isEmpty(q)) {
printf("Queue is empty!\n");
return t;
}
t = q->tasks[q->front];
if (q->front == q->rear) {
q->front = q->rear = -1;
} else {
q->front++;
}
return t;
}
void processQueue(Queue *q, const char *taskType) {
while (!isEmpty(q)) {
Task t = dequeue(q);
printf("Processing %s: %s\n", taskType, t.name);
}
}
int main() {
Queue downloadQ, musicQ, gameQ;
initQueue(&downloadQ);
initQueue(&musicQ);
initQueue(&gameQ);
int n, choice;
Task t;
printf("Enter number of tasks: ");
scanf("%d", &n);
getchar();
for (int i = 0; i < n; i++) {
printf("\nEnter task name: ");
fgets(t.name, sizeof(t.name), stdin);
t.name[strcspn(t.name, "\n")] = 0;
printf("Enter task type (1-Download, 2-Music, 3-Game): ");
scanf("%d", &t.priority);
getchar();
if (t.priority == 1)
enqueue(&downloadQ, t);
else if (t.priority == 2)
enqueue(&musicQ, t);
else if (t.priority == 3)
enqueue(&gameQ, t);
else
printf("Invalid priority!\n");
}
printf("\n--- Processing Download Tasks ---\n");
processQueue(&downloadQ, "Download");
printf("\n--- Processing Music Tasks ---\n");
processQueue(&musicQ, "Music");
printf("\n--- Processing Game Tasks ---\n");
processQueue(&gameQ, "Game");
return 0;
}
