#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define ROWS 1000
#define COLS 1000
#define BLOCK_SIZE 16 

// Function to print a matrix (first 10x10 elements)
void printMatrix(int matrix[ROWS][COLS], const char* name) {
    printf("\n%s (First 10x10 Elements):\n", name);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// OpenMP Static Scheduling Transpose
void transposeMatrixStatic(int matrix[ROWS][COLS], int transposed[COLS][ROWS], int num_threads) {
    omp_set_num_threads(num_threads);  // Set number of threads

    double start_time = omp_get_wtime();

    #pragma omp parallel for collapse(2) schedule(static, BLOCK_SIZE)
    for (int i = 0; i < ROWS; i += BLOCK_SIZE) {
        for (int j = 0; j < COLS; j += BLOCK_SIZE) {
            for (int ii = i; ii < i + BLOCK_SIZE && ii < ROWS; ii++) {
                for (int jj = j; jj < j + BLOCK_SIZE && jj < COLS; jj++) {
                    transposed[jj][ii] = matrix[ii][jj];
                }
            }
        }
    }

    double end_time = omp_get_wtime();
    printf("Threads: %d, Scheduling: Static, Execution Time: %f seconds\n", num_threads, end_time - start_time);
}

int main() {
    int matrix[ROWS][COLS];
    int transposed[COLS][ROWS];

    // Generate random numbers
    srand(time(NULL));

    // Initialize matrix with random values
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matrix[i][j] = rand() % 100;
        }
    }

    // Print original matrix (first 10x10 elements)
    printMatrix(matrix, "Original Matrix");

    // Test different thread counts
    int thread_counts[] = {2, 4, 8};
    for (int i = 0; i < 3; i++) {
        transposeMatrixStatic(matrix, transposed, thread_counts[i]);
    }

    // Print transposed matrix (first 10x10 elements)
    printMatrix(transposed, "Transposed Matrix");

    return 0;
}
