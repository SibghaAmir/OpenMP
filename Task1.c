#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 1000
#define COLS 1000

void transposeMatrix(int matrix[ROWS][COLS], int transposed[COLS][ROWS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }
}

int main() {
    int matrix[ROWS][COLS];
    int transposed[COLS][ROWS];

    // Generate random numbers for different values each run
    srand(time(NULL));

    // Initialize matrix with random values
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matrix[i][j] = rand() % 100;
        }
    }

    printf("Original Matrix (First 10x10 Elements):\n");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }

    clock_t start = clock();
    transposeMatrix(matrix, transposed);
    clock_t end = clock();

    printf("\nTransposed Matrix (First 10x10 Elements):\n");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%2d ", transposed[i][j]);
        }
        printf("\n");
    }

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nExecution Time: %f seconds\n", time_taken);

    return 0;
}