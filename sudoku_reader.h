#ifndef SUDOKU_READER_H
#define SUDOKU_READER_H

int** allocate_matrix(int rows, int cols);
int** allocate_empty_matrix(int rows, int cols);
int** read_matrix(char *path);
void free_matrix(int** matrix, int rows);
void display_matrix(int **mat);


#endif
