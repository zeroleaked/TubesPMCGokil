#include <stdlib.h>
#include <stdio.h>
#include "matrices.h"

double** createMatrix(int n) {
    double* values = calloc(n*n, sizeof(double));
    double** rows = calloc(n, sizeof(double*));
    int i,j;
    for (i=0; i<n; ++i) 
        for (j = 0; j< n; j++) {
            rows[i] = values + i*n;
        }
    return rows;
}

void destroyMatrix(double** matrix) {
    free(*matrix);
    free(matrix);
}

void inputMatrix(double **mat,int n){
    int i , j;
    for (i = 0; i < n; i++){
        for (j = 0;j < n; j++){
            scanf("%lf", mat[i] + j);
        }
    }
}


void printMatrix(double **mat, int n){
    int i = 0, j = 0;
    for (;i < n; i++){
        for (j = 0; j < n; j++){
             printf("%f ", mat[i][j]);
        }
         printf("\n");
    }
    printf("\n");
}

void printArray(double *mat, int n){
    int i = 0;
    for (;i < n; i++){
        printf("%f ", mat[i]);
    }
    printf("\n");
}

void swapRow(double **m, int a, int b , int n){
    int i;
    double temp;
    for (i =0; i < n; i++){
        temp = *(m[a] + i);
        *(m[a] + i) = *(m[b] + i);
        *(m[b] + i) = temp;
    }
}


double findDeterminant(double** mat, int n){ 
    int i , j, k;
    double **m;
    m = (double**) malloc(n * sizeof(double*));

    for ( i = 0; i < n; i++){
        m[i] = (double*)malloc(n * sizeof(double));
    }
    for (i =0; i < n; i++){
        j = 0;
        for (j = 0; j < n ;j++){
            m[i][j] = mat[i][j];
            // printf("m[%d][%d] = %f ", i, j, m[i][j]);
        }
        // printf("%d \n ", i);
    }
    double l[n][n], u[n][n];
    double ratio;
    int sgn = 1;
    i = 0;
    int swap = 1;
    while (i < n){
        if (m[i][i] == 0){
            if (swap + i < n ){
                swapRow(m,i,i+swap,n);
                sgn = sgn * -1;
                swap++;
                i = i-1;
            }
            else{
                // printMatrix(m,n);
                return 0;
            }
        }
        else{
            swap = 1;
            for (j = i+1; j < n; j++ ){
                ratio = m[j][i] / m[i][i];
                for (k = 0; k < n; k++){
                    m[j][k] -= ratio*m[i][k];
                }
            }
        }

        i++;
    }
    //printMatrix(m,n);
    double res = 1;

    for (i = 0; i < n; i++){
        res = res * m[i][i];
        // printf("%f \n", res);
    }

    free(m);

    return res * sgn;

}

double **matrixMultiplication(int p1, int l1, int p2, int l2, double** matriks1, double** matriks2){
  int i, j, k, hasil = 0;
  double** matriksKali;
  matriksKali = (double**)malloc(p1*sizeof(double*));
  for (j = 0; j < l2; j++){
      matriksKali[j] = (double*)malloc(l2*sizeof(double));
  }
  for (i = 0; i < p1; i++) {
    for (j = 0; j < l2; j++) {
      for (k = 0; k < p2; k++) {
        hasil = hasil + matriks1[i][k] * matriks2[k][j];
      }
      matriksKali[i][j] = hasil;
      hasil = 0;
    }
  }
  return matriksKali;
}

double *matrixMultSquareTimesOneColumn(int size, double **matriks1, double *matriks2)
{
    int i, j;
    double* matriksKali;
    matriksKali = (double*)calloc(size,sizeof(double));
    for (i = 0; i < size; i++){
        for (j = 0; j < size; j++){
            matriksKali[i] += matriks1[i][j] * matriks2[j];
        }
    }
    return matriksKali;
}

void scalarMatrixMultiplication(double num ,int p,double *matriks){
    int i,j;
    for (i = 0; i < p; i++){
        
            matriks[i] *= num;
    }
}
void getCofactor(double** A, double** temp, int p, int q, int n) {
  //cofactor of A[p][q]
    int i = 0, j = 0;
    int row, col;
    for (row = 0; row < n; row++) {
        for (col = 0; col < n; col++) {
            if (row != p && col != q) {
                temp[i][j++] = A[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

double** adjoint(double** matrix, int n) {
    double** adj = createMatrix(n);
    if (n == 1) {
        adj[0][0] = 1;
        return adj;
    }
    // store cofactors of A[][]
    double** temp = createMatrix(n);

    int i , j;
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            getCofactor(matrix, temp, i, j, n);
            // sign of adj[j][i] positive if sum of row and column indexes is even.
            double sign = ((i+j)%2==0)? 1: -1;
            // Interchanging i and j to get transpose
            adj[j][i] = (sign)*(findDeterminant(temp, n-1));
        }
    }
    destroyMatrix(temp);
    return adj;
}
