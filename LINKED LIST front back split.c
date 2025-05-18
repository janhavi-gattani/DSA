#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void pushEnd(struct Node** head, int val) {
    struct Node* new = malloc(sizeof(struct Node));
    new->data = val; new->next = NULL;
    if (!*head) *head = new;
    else {
        struct Node* temp = *head;
        while (temp->next) temp = temp->next;
        temp->next = new;
    }
}

void printList(struct Node* head) {
    while (head) { printf("%d ", head->data); head = head->next; }
    printf("\n");
}

void FrontBackSplit(struct Node* src, struct Node** front, struct Node** back) {
    struct Node *slow = src, *fast = src ? src->next : NULL;
    if (!src || !src->next) { *front = src; *back = NULL; return; }
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    *front = src;
    *back = slow->next;
    slow->next = NULL;
}

int main() {
    struct Node *head = NULL, *front = NULL, *back = NULL;
    int n, val;

    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("Enter elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        pushEnd(&head, val);
    }

    FrontBackSplit(head, &front, &back);

    printf("Front List: "); printList(front);
    printf("Back List : "); printList(back);

    return 0;
}
