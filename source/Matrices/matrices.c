#include <stdlib.h>
#include <stdio.h>

// #define TESTUNIT
// #define DETERMINANT
// #define INVERSEMATRIX
#ifdef TESTUNIT
void printMatrix(double **mat, int n){
    int i = 0, j = 0;
    for (;i < n; i++){
        for (j = 0; j < n; j++){
             printf("%f\t", mat[i][j]);
        }
         printf("\n");
    }
    printf("\n");
}

void printArray(double *mat, int n){
    for (int i = 0; i < n; i++){
        printf("%f\n", mat[i]);
    }
    printf("\n");
}
#endif

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

void destroyMatrix(double*** matrix) {
    free(**matrix);
    free(*matrix);
}

double* createArray(int n) {
  double* array;
  array = (double*) malloc(n * sizeof(double));
  for (int i = 0; i < n; i++) {
    array[i] = 0;
  }
  return array;
}

void destroyArray(double **array) {
  free(*array);
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
        }
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
            else return 0;
        }
        else {
            swap = 1;
            for (j = i+1; j < n; j++ ) {
                ratio = m[j][i] / m[i][i];
                for (k = 0; k < n; k++)
                    m[j][k] -= ratio*m[i][k];
            }
        }
        i++;
    }
    double res = 1;
    for (i = 0; i < n; i++)
        res = res * m[i][i];
    free(m);
    return res * sgn;

}

void scalarMatrixMultiplication(double num, int p, double ***matriks){
    int i,j;
    for (int i = 0; i < p; i++)
      for (int j = 0; j < p; j++)
          (*matriks)[i][j] *= num;
}

void getCofactor(double** A, double** temp, int p, int q, int n) {
    int i = 0, j = 0;
    int row, col;
    for (row = 0; row < n; row++)
        for (col = 0; col < n; col++)
            if (row != p && col != q) {
                temp[i][j++] = A[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
}

double** adjoint(double** matrix, int n) {
    double** adj = createMatrix(n);
    if (n == 1) {
        adj[0][0] = 1;
        return adj;
    }
    double** temp = createMatrix(n);
    int i , j;
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            getCofactor(matrix, temp, i, j, n);
            double sign = ((i+j)%2==0)? 1: -1;
            adj[j][i] = (sign)*(findDeterminant(temp, n-1));
        }
    }
    destroyMatrix(&temp);
    return adj;
}

double* matrixArrayMultiplication(double** matrix, double* array, int size) {
  double* result = createArray(size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      result[i] += matrix[i][j] * array[j];
    }
  }
  return result;
}

void createInverseMatrix( double **matrix, int matrix_length, double ***inverse) {
  *inverse = adjoint(matrix, matrix_length);
  double det = findDeterminant(matrix, matrix_length);
  scalarMatrixMultiplication(1/det, matrix_length, inverse);
}
#ifdef TESTUNIT
int main(){
    #ifdef DETERMINANT
    int total;
    scanf("%d",&total);

    int n;
    while(total--){
        scanf("%d", &n);
        double **arr = createMatrix(n);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                scanf("%lf",arr[i]+j);
            }
        }
        double ans = findDeterminant(arr, n);
        printf("%f\n",ans);
    }
    #endif

    #ifdef INVERSEMATRIX
    int total;
    scanf("%d",&total);

    int n;
    while(total--){
        scanf("%d", &n);
        double **arr = createMatrix(n);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                scanf("%lf",arr[i]+j);
            }
        }
        double** ans = createMatrix(n);
        createInverseMatrix(arr,n,&ans);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                printf("%.17f ",ans[i][j]);
            }
            printf("\n");
        }
    }
    #endif
    return 0;
}
#endif