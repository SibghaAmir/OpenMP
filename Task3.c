#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define ROWS 1000
#define COLS 1000
#define BLOCK_SIZE 16 

void transposeMatrix(int matrix[ROWS][COLS], int transposed[COLS][ROWS]) {
#pragma omp parallel for collapse(2)
    for (int i = 0; i < ROWS; i += BLOCK_SIZE) {
        for (int j = 0; j < COLS; j += BLOCK_SIZE) {
            for (int ii = i; ii < i + BLOCK_SIZE && ii < ROWS; ii++) {
                for (int jj = j; jj < j + BLOCK_SIZE && jj < COLS; jj++) {
                    transposed[jj][ii] = matrix[ii][jj];
                }
            }
        }
    }
}

int main() {
    int matrix[ROWS][COLS];
    int transposed[COLS][ROWS];

    // Generate random numbers
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

    double start = omp_get_wtime();
    transposeMatrix(matrix, transposed);
    double end = omp_get_wtime();

    printf("\nTransposed Matrix (First 10x10 Elements):\n");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%2d ", transposed[i][j]);
        }
        printf("\n");
    }

    printf("\nExecution Time: %f seconds with %d threads\n", end - start, omp_get_max_threads());

    return 0;
}