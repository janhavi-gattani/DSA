#include <stdio.h>
#include <string.h>

typedef struct {
    char name[30];
    int roll;
    int marks;
} Student;

void swap(Student *a, Student *b, int *count) {
    Student t = *a; *a = *b; *b = t;
    (*count)++;
}

// Heap Sort functions
void heapify(Student arr[], int n, int i, int *count) {
    int largest = i, left = 2*i + 1, right = 2*i + 2;
    if (left < n && arr[left].roll > arr[largest].roll) largest = left;
    if (right < n && arr[right].roll > arr[largest].roll) largest = right;
    if (largest != i) {
        swap(&arr[i], &arr[largest], count);
        heapify(arr, n, largest, count);
    }
}

void heapSort(Student arr[], int n, int *count) {
    for (int i = n/2 -1; i >= 0; i--) heapify(arr, n, i, count);
    for (int i = n-1; i > 0; i--) {
        swap(&arr[0], &arr[i], count);
        heapify(arr, i, 0, count);
    }
}

// Merge Sort functions
void merge(Student arr[], int l, int m, int r, int *count) {
    int n1 = m - l + 1, n2 = r - m;
    Student L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];

    int i=0, j=0, k=l;
    while (i < n1 && j < n2) {
        if (L[i].roll <= R[j].roll) arr[k++] = L[i++];
        else {
            arr[k++] = R[j++];
            (*count)++;  // Counting swap here as inversion
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(Student arr[], int l, int r, int *count) {
    if (l < r) {
        int m = (l + r)/2;
        mergeSort(arr, l, m, count);
        mergeSort(arr, m+1, r, count);
        merge(arr, l, m, r, count);
    }
}

void printStudents(Student arr[], int n) {
    for (int i=0; i<n; i++)
        printf("%s %d %d\n", arr[i].name, arr[i].roll, arr[i].marks);
}

int main() {
    int n, choice, swaps = 0;
    printf("Enter number of students: ");
    scanf("%d", &n);
    Student arr[n];
    for (int i=0; i<n; i++) {
        printf("Enter name, roll, marks of student %d:\n", i+1);
        scanf("%s %d %d", arr[i].name, &arr[i].roll, &arr[i].marks);
    }

    printf("Choose sorting:\n1. Heap Sort\n2. Merge Sort\nEnter choice: ");
    scanf("%d", &choice);

    swaps = 0;
    if (choice == 1) {
        heapSort(arr, n, &swaps);
        printf("Sorted by Heap Sort:\n");
    } else if (choice == 2) {
        mergeSort(arr, 0, n-1, &swaps);
        printf("Sorted by Merge Sort:\n");
    } else {
        printf("Invalid choice\n");
        return 1;
    }

    printStudents(arr, n);
    printf("Number of swaps (or inversions for merge sort): %d\n", swaps);

    return 0;
}
