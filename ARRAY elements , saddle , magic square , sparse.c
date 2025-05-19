          #include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10
#define MAX_SPARSE 100

// Function prototypes
int countMissingNumbers(int arr[], int n);
void findSaddlePoint(int matrix[][MAX_SIZE], int rows, int cols);
int isMagicSquare(int square[][MAX_SIZE], int size);
void convertToSparse(int matrix[][MAX_SIZE], int rows, int cols);
void printMatrix(int matrix[][MAX_SIZE], int rows, int cols);

int main() {
    int choice;

    do {
        printf("\nArray/Matrix Operations Menu:\n");
        printf("1. Count missing numbers in sequence\n");
        printf("2. Find saddle point in matrix\n");
        printf("3. Check if matrix is magic square\n");
        printf("4. Convert matrix to sparse form\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: {
                // Problem A: Count missing numbers in sequence
                int n;
                printf("Enter number of elements in array: ");
                scanf("%d", &n);

                int arr[n];
                printf("Enter %d elements: ", n);
                for(int i = 0; i < n; i++) {
                    scanf("%d", &arr[i]);
                }

                printf("Missing numbers count: %d\n", countMissingNumbers(arr, n));
                break;
            }

            case 2: {
                // Problem B: Find saddle point in matrix
                int rows, cols;
                printf("Enter number of rows and columns: ");
                scanf("%d %d", &rows, &cols);

                int matrix[MAX_SIZE][MAX_SIZE];
                printf("Enter matrix elements:\n");
                for(int i = 0; i < rows; i++) {
                    for(int j = 0; j < cols; j++) {
                        scanf("%d", &matrix[i][j]);
                    }
                }

                printf("\nInput Matrix:\n");
                printMatrix(matrix, rows, cols);
                findSaddlePoint(matrix, rows, cols);
                break;
            }

            case 3: {
                // Problem C: Check magic square
                int size;
                printf("Enter size of square matrix: ");
                scanf("%d", &size);

                int matrix[MAX_SIZE][MAX_SIZE];
                printf("Enter matrix elements:\n");
                for(int i = 0; i < size; i++) {
                    for(int j = 0; j < size; j++) {
                        scanf("%d", &matrix[i][j]);
                    }
                }

                printf("\nInput Matrix:\n");
                printMatrix(matrix, size, size);
                if(isMagicSquare(matrix, size)) {
                    printf("It is a Magic Square!\n");
                } else {
                    printf("It is NOT a Magic Square.\n");
                }
                break;
            }

            case 4: {
                // Problem D: Convert to sparse form
                int rows, cols;
                printf("Enter number of rows and columns: ");
                scanf("%d %d", &rows, &cols);

                int matrix[MAX_SIZE][MAX_SIZE];
                printf("Enter matrix elements:\n");
                for(int i = 0; i < rows; i++) {
                    for(int j = 0; j < cols; j++) {
                        scanf("%d", &matrix[i][j]);
                    }
                }

                printf("\nInput Matrix:\n");
                printMatrix(matrix, rows, cols);
                convertToSparse(matrix, rows, cols);
                break;
            }

            case 5:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 5);

    return 0;
}

// Problem A: Count missing numbers in sequence
int countMissingNumbers(int arr[], int n) {
    if(n == 0) return 0;

    // Find min and max in array
    int min = arr[0], max = arr[0];
    for(int i = 1; i < n; i++) {
        if(arr[i] < min) min = arr[i];
        if(arr[i] > max) max = arr[i];
    }

    // The count of numbers between min and max is (max - min + 1)
    // Missing numbers = total possible - actual numbers
    return (max - min + 1) - n;
}

// Problem B: Find saddle point in matrix
void findSaddlePoint(int matrix[][MAX_SIZE], int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        // Find the minimum element in current row
        int min_row = matrix[i][0], col_ind = 0;
        for(int j = 1; j < cols; j++) {
            if(matrix[i][j] < min_row) {
                min_row = matrix[i][j];
                col_ind = j;
            }
        }

        // Check if the minimum of row is also maximum of its column
        int k;
        for(k = 0; k < rows; k++) {
            if(matrix[k][col_ind] > min_row)
                break;
        }

        if(k == rows) {
            printf("Saddle Point found at (%d, %d): %d\n", i, col_ind, min_row);
            return;
        }
    }
    printf("No Saddle Point found\n");
}

// Problem C: Check if matrix is magic square
int isMagicSquare(int square[][MAX_SIZE], int size) {
    // Calculate the sum of the first row
    int sum = 0;
    for(int j = 0; j < size; j++)
        sum += square[0][j];

    // Check rows
    for(int i = 1; i < size; i++) {
        int row_sum = 0;
        for(int j = 0; j < size; j++)
            row_sum += square[i][j];
        if(row_sum != sum) return 0;
    }

    // Check columns
    for(int j = 0; j < size; j++) {
        int col_sum = 0;
        for(int i = 0; i < size; i++)
            col_sum += square[i][j];
        if(col_sum != sum) return 0;
    }

    // Check main diagonal
    int diag_sum = 0;
    for(int i = 0; i < size; i++)
        diag_sum += square[i][i];
    if(diag_sum != sum) return 0;

    // Check secondary diagonal
    diag_sum = 0;
    for(int i = 0; i < size; i++)
        diag_sum += square[i][size-1-i];
    if(diag_sum != sum) return 0;

    return 1;
}

// Problem D: Convert matrix to sparse form
void convertToSparse(int matrix[][MAX_SIZE], int rows, int cols) {
    typedef struct {
        int row;
        int col;
        int value;
    } SparseElement;

    SparseElement sparse[MAX_SPARSE];
    int k = 0;

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(matrix[i][j] != 0) {
                sparse[k].row = i;
                sparse[k].col = j;
                sparse[k].value = matrix[i][j];
                k++;
            }
        }
    }

    printf("\nSparse Representation:\n");
    printf("Row\tColumn\tValue\n");
    for(int i = 0; i < k; i++) {
        printf("%d\t%d\t%d\n", sparse[i].row, sparse[i].col, sparse[i].value);
    }
}

// Helper function to print matrix
void printMatrix(int matrix[][MAX_SIZE], int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
}
