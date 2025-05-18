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

// Heapify for Heap Sort
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

// Partition for Quick Sort (first element as pivot)
int partition(Student arr[], int low, int high, int *count) {
    int pivot = arr[low].roll;
    int i = low + 1, j = high;

    while (1) {
        while (i <= high && arr[i].roll <= pivot) i++;
        while (arr[j].roll > pivot) j--;

        if (i < j) {
            swap(&arr[i], &arr[j], count);
        } else {
            break;
        }
    }
    swap(&arr[low], &arr[j], count);
    return j;
}

void quickSort(Student arr[], int low, int high, int *count) {
    if (low < high) {
        int pi = partition(arr, low, high, count);
        quickSort(arr, low, pi - 1, count);
        quickSort(arr, pi + 1, high, count);
    }
}

void printStudents(Student arr[], int n) {
    for(int i=0; i<n; i++)
        printf("%s %d %d\n", arr[i].name, arr[i].roll, arr[i].marks);
}

int main() {
    int n, choice, swaps = 0;
    printf("Enter number of students: ");
    scanf("%d", &n);
    Student arr[n];
    for(int i=0; i<n; i++) {
        printf("Enter name, roll, marks of student %d:\n", i+1);
        scanf("%s %d %d", arr[i].name, &arr[i].roll, &arr[i].marks);
    }

    printf("Choose sorting method:\n1. Heap Sort\n2. Quick Sort (first element as pivot)\nEnter choice: ");
    scanf("%d", &choice);

    swaps = 0;
    if (choice == 1) {
        heapSort(arr, n, &swaps);
        printf("Sorted by Heap Sort:\n");
    } else if (choice == 2) {
        quickSort(arr, 0, n-1, &swaps);
        printf("Sorted by Quick Sort (first element as pivot):\n");
    } else {
        printf("Invalid choice\n");
        return 1;
    }

    printStudents(arr, n);
    printf("Number of swaps: %d\n", swaps);
    return 0;
}
