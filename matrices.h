#ifndef MATRICES_H
#define MATRICES_H

#define MAX 10000
// main function here is swapRow and luDecomposition
void inputMatrix(float** mat, int n);
void swapRow(float **m, int a, int b , int n);
void printMatrix(float **mat, int n);
float luDecomposition(float** mat, int n) ;

#endif