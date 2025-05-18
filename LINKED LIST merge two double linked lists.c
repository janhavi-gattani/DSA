#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

struct Node* insertEnd(struct Node* head, int data) {
    struct Node* newNode = createNode(data);
    if (head == NULL)
        return newNode;

    struct Node* temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
    newNode->prev = temp;
    return head;
}

struct Node* mergeSorted(struct Node* a, struct Node* b) {
    struct Node* result = NULL, *tail = NULL;

    while (a && b) {
        struct Node* minNode;
        if (a->data < b->data) {
            minNode = a;
            a = a->next;
        } else {
            minNode = b;
            b = b->next;
        }
        minNode->prev = minNode->next = NULL;

        if (result == NULL) {
            result = tail = minNode;
        } else {
            tail->next = minNode;
            minNode->prev = tail;
            tail = minNode;
        }
    }

    struct Node* rem = (a != NULL) ? a : b;
    while (rem) {
        struct Node* next = rem->next;
        rem->next = NULL;
        if (tail) {
            tail->next = rem;
            rem->prev = tail;
            tail = rem;
        } else {
            result = tail = rem;
        }
        rem = next;
    }

    return result;
}

void display(struct Node* head) {
    struct Node* temp = head;
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int n1, n2, val;
    struct Node *head1 = NULL, *head2 = NULL;

    printf("Enter number of elements in first sorted list: ");
    scanf("%d", &n1);
    printf("Enter elements of first list (sorted): ");
    for (int i = 0; i < n1; i++) {
        scanf("%d", &val);
        head1 = insertEnd(head1, val);
    }

    printf("Enter number of elements in second sorted list: ");
    scanf("%d", &n2);
    printf("Enter elements of second list (sorted): ");
    for (int i = 0; i < n2; i++) {
        scanf("%d", &val);
        head2 = insertEnd(head2, val);
    }

    struct Node* merged = mergeSorted(head1, head2);

    printf("Merged Sorted List: ");
    display(merged);

    return 0;
}
