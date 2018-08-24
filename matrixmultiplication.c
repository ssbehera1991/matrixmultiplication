#include <stdio.h>
#include <stdlib.h>

int ** alloc_matrix(int size_of_2d_matrix)
{
	int i;
	int **matrix;

	matrix = (int **)malloc(sizeof(int *) * size_of_2d_matrix);
	for (i = 0; i < size_of_2d_matrix; i++)
		matrix[i] = (int *) malloc(sizeof(int) * size_of_2d_matrix);

	return matrix;
}

int ** alloc_matrix_with_0s(int size_of_2d_matrix)
{
	int i;
	int **matrix;

	matrix = (int **) malloc(sizeof(int *) * size_of_2d_matrix);
	for (i = 0; i < size_of_2d_matrix; i++) {
		matrix[i] = calloc(sizeof(int), size_of_2d_matrix);
	}

	return matrix;
}

int ** alloc_matrix_with_1s(int size_of_2d_matrix)
{
	int i, j;
	int **matrix;

	matrix = alloc_matrix(size_of_2d_matrix);
	for (i = 0; i < size_of_2d_matrix; i++) {
		for (j = 0; j < size_of_2d_matrix; j++) {
			matrix[i][j] = 1;
		}
	}

	return matrix;
}

#define MAX_MATRIX_PRINT_SIZE 5

void print_matrix(int **matrix, int size_of_2d_matrix)
{
	int i, j;
	int print_size = size_of_2d_matrix < MAX_MATRIX_PRINT_SIZE ?
				size_of_2d_matrix:MAX_MATRIX_PRINT_SIZE;

	for (i = 0; i < print_size; i++) {
		for (j = 0; j < print_size; j++) {
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}
}

void free_matrix(int **matrix, int size_of_2d_matrix)
{
	int i;

	for (i = 0; i < size_of_2d_matrix; i++)
		free(matrix[i]);
	free(matrix);
}

void matrix_mult(int **matrix1, int **matrix2, int size_of_2d_matrix)
{
	int i, j, k;
	int **matrix3;
	clock_t ticks;

	matrix3 = alloc_matrix_with_0s(size_of_2d_matrix);

	ticks = clock();
	for (i = 0; i < size_of_2d_matrix; i++) {
		for (j = 0; j < size_of_2d_matrix; j++) {
			for(k = 0; k < size_of_2d_matrix; k++) {
				matrix3[i][j] = matrix1[i][k] * matrix2[k][j] + matrix3[i][j];
			}
		}
	}

	ticks = clock() - ticks;

	printf("Multiplication results: %d\n\n", (int)ticks);
	print_matrix(matrix3, size_of_2d_matrix);
	printf("\n");
	free_matrix(matrix3, size_of_2d_matrix);
}

void matrix_mult_optimized(int **matrix1, int **matrix2, int size_of_2d_matrix)
{
	int i, j, k;
	int **matrix3;
	clock_t ticks;

	matrix3 = alloc_matrix_with_0s(size_of_2d_matrix);

	ticks = clock();

	for (i = 0; i < size_of_2d_matrix; i++) {
		for (j = 0; j < size_of_2d_matrix; j++) {
			for (k = 0; k < size_of_2d_matrix; k++) {
				matrix3[j][k] = matrix1[j][i] * matrix2[i][k] + matrix3[j][k];
			}
		}
	}

	ticks = clock() - ticks;

	printf("Optimized multiplication results: %d\n\n", (int)ticks);
	print_matrix(matrix3, size_of_2d_matrix);
	printf("\n");
	free_matrix(matrix3, size_of_2d_matrix);
}

int main(void)
{
	int size_of_2d_matrix;
	int **matrix1, **matrix2;
	
	printf("Enter the size of the matrix:");
	scanf("%d", &size_of_2d_matrix);

	matrix1 = alloc_matrix_with_1s(size_of_2d_matrix);
	matrix2 = alloc_matrix_with_1s(size_of_2d_matrix);

	matrix_mult(matrix1, matrix2, size_of_2d_matrix);

	matrix_mult_optimized(matrix1, matrix2, size_of_2d_matrix); 

	return 0;
}
