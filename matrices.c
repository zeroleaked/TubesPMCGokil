#include <stdlib.h>
#include <stdio.h>
#include "matrices.h"

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
            // printf("%f ", mat[i][j]);
        }
        // printf("\n");
    }
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
    printMatrix(m,n);
    float res = 1;

    for (i = 0; i < n; i++){
        res = res * m[i][i];
        // printf("%f \n", res);
    }

    free(m);

    return res * sgn;

}
