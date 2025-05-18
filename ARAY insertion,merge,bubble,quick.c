#include <stdio.h>
#include <string.h>

typedef struct {
    char name[20];
    int roll, marks;
} Student;

void swap(Student *a, Student *b, int *count) {
    Student t = *a; *a = *b; *b = t; (*count)++;
}

// Insertion Sort
void insertion(Student a[], int n, int *count) {
    for (int i = 1; i < n; i++)
        for (int j = i; j > 0 && a[j].roll < a[j-1].roll; j--)
            swap(&a[j], &a[j-1], count);
}

// Bubble Sort
void bubble(Student a[], int n, int *count) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (a[j].roll > a[j+1].roll)
                swap(&a[j], &a[j+1], count);
}

// Merge Sort
void merge(Student a[], int l, int m, int r, int *count) {
    int i = l, j = m+1, k = 0;
    Student temp[r-l+1];
    while (i <= m && j <= r)
        temp[k++] = (a[i].roll < a[j].roll) ? a[i++] : a[j++];
    while (i <= m) temp[k++] = a[i++];
    while (j <= r) temp[k++] = a[j++];
    for (i = l, k = 0; i <= r; i++, k++) a[i] = temp[k], (*count)++;
}

void mergeSort(Student a[], int l, int r, int *count) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(a, l, m, count);
        mergeSort(a, m+1, r, count);
        merge(a, l, m, r, count);
    }
}

// Quick Sort
int partition(Student a[], int l, int r, int *count) {
    int p = a[r].roll, i = l-1;
    for (int j = l; j < r; j++)
        if (a[j].roll < p)
            swap(&a[++i], &a[j], count);
    swap(&a[i+1], &a[r], count);
    return i+1;
}

void quickSort(Student a[], int l, int r, int *count) {
    if (l < r) {
        int pi = partition(a, l, r, count);
        quickSort(a, l, pi-1, count);
        quickSort(a, pi+1, r, count);
    }
}

void print(Student a[], int n) {
    printf("\nSorted list:\n");
    for (int i = 0; i < n; i++)
        printf("Name: %s, Roll: %d, Marks: %d\n", a[i].name, a[i].roll, a[i].marks);
}

int main() {
    int n, ch, count;
    printf("Enter number of students: ");
    scanf("%d", &n);
    Student a[n], temp[n];

    for (int i = 0; i < n; i++) {
        printf("Enter name, roll no, marks for student %d: ", i+1);
        scanf("%s %d %d", a[i].name, &a[i].roll, &a[i].marks);
    }

    while (1) {
        printf("\n1.Insertion Sort\n2.Bubble Sort\n3.Merge Sort\n4.Quick Sort\n5.Exit\nEnter choice: ");
        scanf("%d", &ch);
        memcpy(temp, a, sizeof(a));
        count = 0;

        switch (ch) {
            case 1: insertion(temp, n, &count); break;
            case 2: bubble(temp, n, &count); break;
            case 3: mergeSort(temp, 0, n-1, &count); break;
            case 4: quickSort(temp, 0, n-1, &count); break;
            case 5: return 0;
            default: printf("Invalid choice!\n"); continue;
        }
        print(temp, n);
        printf("Number of swaps: %d\n", count);
    }
}
