#ifndef MATRICES_H
#define MATRICES_H

#define MAX 10000
// main function here is swapRow and luDecomposition
void inputMatrix(float** mat, int n);
void swapRow(float **m, int a, int b , int n);
void printMatrix(float **mat, int n);
float findDeterminant(float** mat, int n) ;
double matrixMultiplication(int p1, int l1, int p2, int l2, double** matriks1, double** matriks2);

float** createMatrix(int n);
void destroyMatrix(float** matrix);
float** adjoint(float** matrix, int n);

#endif
