#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX_SIZE 2000  // Maximum matrix size

// Function to initialize matrix
void initialize_matrix(double A[MAX_SIZE][MAX_SIZE], int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = (i + j) * 0.01;
        }
    }
}

// *Collapse with Static Scheduling & Chunk Size*
double collapse_with_chunk(double A[MAX_SIZE][MAX_SIZE], double B[MAX_SIZE][MAX_SIZE], int N, int chunk_size) {
    double start = omp_get_wtime();

    #pragma omp parallel for schedule(static, chunk_size) collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] += B[i][j];
        }
    }

    return omp_get_wtime() - start;
}

int main() {
    int sizes[] = {512, 1024, 2000}; // Different matrix sizes
    int num_threads[] = {4, 8};      // Testing with 4 and 8 threads
    int chunk_sizes[] = {128,250}; // Testing different chunk sizes

    for (int t = 0; t < 2; t++) {
        omp_set_num_threads(num_threads[t]);
        printf("\n=== Running with %d Threads ===\n", num_threads[t]);

        for (int c = 0; c < 2; c++) {
            int chunk_size = chunk_sizes[c];
            printf("\n--- Using Chunk Size: %d ---\n", chunk_size);

            for (int s = 0; s < 3; s++) {
                int N = sizes[s];

                static double A[MAX_SIZE][MAX_SIZE], B[MAX_SIZE][MAX_SIZE];
                initialize_matrix(A, N);
                initialize_matrix(B, N);

                double exec_time = collapse_with_chunk(A, B, N, chunk_size);

                printf("Matrix Size: %d x %d, Chunk Size: %d, Execution Time: %.6f sec\n",
                       N, N, chunk_size, exec_time);
            }
        }
    }

    return 0;
}
