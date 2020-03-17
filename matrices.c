#include <stdlib.h>
#include <stdio.h>
#include "matrices.h"

float** createMatrix(int n) {
    float* values = calloc(n*n, sizeof(float));
    float** rows = calloc(n, sizeof(float*));
    for (int i=0; i<n; ++i) for (int j = 0; j< n; j++) {
        rows[i] = values + i*n;
    }
    return rows;
}

void destroyMatrix(float** matrix) {
    free(*matrix);
    free(matrix);
}

void inputMatrix(float **mat,int n){
    int i , j;
    for (i = 0; i < n; i++){
        for (j = 0;j < n; j++){
            scanf("%f", mat[i] + j);
        }
    }
}


void printMatrix(float **mat, int n){
    int i = 0, j = 0;
    for (;i < n; i++){
        for (j = 0; j < n; j++){
             printf("%f ", mat[i][j]);
        }
         printf("\n");
    }
    printf("\n");
}

void swapRow(float **m, int a, int b , int n){
    int i;
    float temp;
    for (i =0; i < n; i++){
        temp = *(m[a] + i);
        *(m[a] + i) = *(m[b] + i);
        *(m[b] + i) = temp;
    }
}


float luDecomposition(float** mat, int n){
    int i , j, k;
    float **m;
    m = (float**) malloc(n * sizeof(float*));

    for ( i = 0; i < n; i++){
        m[i] = (float*)malloc(n * sizeof(float));
    }
    for (i =0; i < n; i++){
        j = 0;
        for (j = 0; j < n ;j++){
            m[i][j] = mat[i][j];
            // printf("m[%d][%d] = %f ", i, j, m[i][j]);
        }
        // printf("%d \n ", i);
    }
    float l[n][n], u[n][n];
    float ratio;
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
    float res = 1;

    for (i = 0; i < n; i++){
        res = res * m[i][i];
        // printf("%f \n", res);
    }

    free(m);

    return res * sgn;

}

void getCofactor(float** A, float** temp, int p, int q, int n) {
  //cofactor of A[p][q]
    int i = 0, j = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
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

float** adjoint(float** matrix, int n) {
    float** adj = createMatrix(n);
    if (n == 1) {
        adj[0][0] = 1;
        return adj;
    }
    // store cofactors of A[][]
    float** temp = createMatrix(n);

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            getCofactor(matrix, temp, i, j, n);
            // sign of adj[j][i] positive if sum of row and column indexes is even.
            float sign = ((i+j)%2==0)? 1: -1;
            // Interchanging i and j to get transpose
            adj[j][i] = (sign)*(luDecomposition(temp, n-1));
        }
    }
    destroyMatrix(temp);
    return adj;
}
