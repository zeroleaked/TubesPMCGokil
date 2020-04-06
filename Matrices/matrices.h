#ifndef MATRICES_H
#define MATRICES_H

#define MAX 10000
// main function here is swapRow and luDecomposition
void inputMatrix(double** mat, int n);
void swapRow(double **m, int a, int b , int n);
void printMatrix(double **mat, int n);
void printArray(double *mat, int n);
double findDeterminant(double** mat, int n) ;
double **matrixMultiplication(int p1, int l1, int p2, int l2, double** matriks1, double** matriks2);
void scalarMatrixMultiplication(double num ,int p,double ***matriks);

double** createMatrix(int n);
double* createArray(int n);
void destroyMatrix(double** matrix);
double** adjoint(double** matrix, int n);
double* matrixArrayMultiplication(double** matrix, double* array, int size); 

#endif
