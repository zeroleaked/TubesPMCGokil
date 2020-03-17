#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "configuration.h"
#include "matrices.h"


int main(){
    int n ;
    float **matrices;
    
    scanf("%d", &n);
    int i;
    matrices = (float**) malloc(n * sizeof(float*));

    for ( i = 0; i < n; i++){
        matrices[i] = (float*)malloc(n * sizeof(float));
    }
    inputMatrix(matrices,n);
    printMatrix(matrices,n);

    float res = luDecomposition(matrices, n) ;

    printf("%f" , res);
    return 0;
}