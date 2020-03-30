#ifndef MATRICES_H
#define MATRICES_H

#define MAX 10000
// main function here is swapRow and luDecomposition
void inputMatrix(double** mat, int n);
void swapRow(double **m, int a, int b , int n);
void printMatrix(double **mat, int n);
double findDeterminant(double** mat, int n) ;
double matrixMultiplication(int p1, int l1, int p2, int l2, double** matriks1, double** matriks2);

double** createMatrix(int n);
void destroyMatrix(double** matrix);
double** adjoint(double** matrix, int n);

#endif
