/* EL2208 Praktikum Pemecahan Masalah dengan C
*Modul       :
*Percobaan   :
*Hari/Tanggal: Friday/13-03-2020
*Nama/NIM    : Oktavianus Irvan Sitanggang/13218071
*Asisten/NIM :
*Nama File   : main.c
*Deskripsi   :
*/


#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "matrices.h"
#include "configuration.h"

int main(){
  int n;
  scanf("%d", &n);
  float** matrix = createMatrix(n);
  inputMatrix(matrix, n);
  printf("\nA\n");
  printMatrix(matrix, n);

  float** adj = adjoint(matrix, n);
  printf("adjoint A\n");
  printMatrix(adj, n);


  printf("det(A) = %f\n",luDecomposition(matrix, n));

  destroyMatrix(adj);
  destroyMatrix(matrix);

  return 0;
}
