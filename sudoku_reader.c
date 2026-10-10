#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int** allocate_matrix(size_t rows, size_t cols) {
    int** matrix = malloc(rows * sizeof(int*));
    if (!matrix) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));
        if (!matrix[i]) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
    }
    return matrix;
}

int** allocate_empty_matrix(size_t rows, size_t cols) {
    int** matrix = calloc(rows, sizeof(int*));
    if (!matrix) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < rows; i++) {
        matrix[i] = calloc(cols, sizeof(int));
        if (!matrix[i]) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
    }
    return matrix;
}

void free_matrix(int** matrix, size_t rows) 
{
    for (size_t i = 0; i < rows; i++) 
    {
        free(matrix[i]);
    }
    free(matrix);
}

int **read_matrix(char * path)
{
	FILE* file = fopen(path, "r");
    if (!file) 
    {
        perror("Error opening file");
        return NULL;
    }

    int rows=9;
    int cols=9;

    int** matrix = allocate_matrix(rows, cols);

    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
	{
            if (fscanf(file, "%d", &matrix[i][j]) != 1) 
	    {
                fprintf(stderr, "Invalid or missing matrix value at [%d][%d].\n", i, j);
                free_matrix(matrix, rows);
                fclose(file);
                return NULL;
            }
        }
    }
    fclose(file);
    return matrix;
}

void display_matrix(int **mat)
{
	for (int i = 0; i < 9; i++) 
	{
        for (int j = 0; j < 9; j++) 
	{
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}
