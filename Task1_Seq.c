#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to initialize a matrix with random values
void initialize_matrix(int **matrix, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 100; // Random values (0-99)
        }
    }
}


// Function to transpose a matrix sequentially
void transposeMatrix(int **matrix, int **transposed, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }
}

int main() {
    srand(time(NULL)); // Seed for random number generation

    int sizes[] = {512, 1024, 2000}; // Different matrix sizes

    for (int s = 0; s < 3; s++) {
        int N = sizes[s];

        // Dynamic memory allocation for matrix
        int **matrix = (int **)malloc(N * sizeof(int *));
        int **transposed = (int **)malloc(N * sizeof(int *));
        for (int i = 0; i < N; i++) {
            matrix[i] = (int *)malloc(N * sizeof(int));
            transposed[i] = (int *)malloc(N * sizeof(int));
        }

        // Initialize matrix
        initialize_matrix(matrix, N);

        // Measure execution time
        clock_t start_time = clock();
        transposeMatrix(matrix, transposed, N);
        clock_t end_time = clock();

        double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("Matrix Size: %d x %d, Execution Time: %f seconds\n", N, N, execution_time);

        // Free allocated memory
        for (int i = 0; i < N; i++) {
            free(matrix[i]);
            free(transposed[i]);
        }
        free(matrix);
        free(transposed);
    }

    return 0;
}
