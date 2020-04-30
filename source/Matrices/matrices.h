#ifndef MATRICES_H
#define MATRICES_H

double** createMatrix(int n);
void destroyMatrix(double ***matrix);
void printMatrix(double **mat, int n);

void createInverseMatrix( double **matrix, int matrix_size, double ***inverse);

double* createArray(int n);
void destroyArray(double **array);
void printArray(double *mat, int n);

double *matrixArrayMultiplication(double** matrix, double* array, int size);

#endif
