#include "../Configuration/configuration.h"
#include "../Matrices/matrices.h"
#include "tableau.h"

#include <stdio.h>
#include <stdlib.h>


void addMatrixA(
  component *component_array,
  int component_array_length,
  int *node_array,
  int node_array_length,
  int ground,
  double ***big_ass_matrix
) {
    int size = node_array_length - 1 + 2 * component_array_length;
    int col_offset = node_array_length - 1 + component_array_length;
    int row_offset = node_array_length - 1;
    int groundPassed = 0;

    for (int j = 0; j < node_array_length; j++) {
      if (ground == node_array[j]) {
        groundPassed = 1;
        continue;
      }
      for (int k = 0; k < component_array_length; k++) {
        if (component_array[k].node1 == node_array[j]) {
          (*big_ass_matrix)[j - groundPassed][col_offset + k] = -1;
          (*big_ass_matrix)[row_offset + k][j - groundPassed] = -1;
        }
        else if (component_array[k].node2 == node_array[j]) {
          (*big_ass_matrix)[j - groundPassed][col_offset + k] = 1;
          (*big_ass_matrix)[row_offset + k][j - groundPassed] = 1;
        }
      }
    }

}

void addIdentity(int offset, int size, double ***big_ass_matrix) {
  for (int i = 0; i < size; i++) {
    (*big_ass_matrix)[offset+i][offset+i] = 1;
  }
}

void addBranch (component *component_array,
  int component_array_length,
  int node_array_length,
  double ***big_ass_matrix,
  double **constant
) {
    int offset2 = node_array_length - 1 + component_array_length;
    int col_offset1 = node_array_length - 1;
    for (int i = 0; i < component_array_length; i++) {
      if ( component_array[i].type == 'R' ) {
        (*big_ass_matrix)[offset2+i][col_offset1+i] = 1;
        (*big_ass_matrix)[offset2+i][offset2+i] = -component_array[i].constant;
      }
      else if ( component_array[i].type == 'V' || component_array[i].type == 'v' ) {
        (*big_ass_matrix)[offset2+i][col_offset1+i] = 1;
        (*constant)[offset2+i] = component_array[i].constant;
      }
      else if ( component_array[i].type == 'I' || component_array[i].type == 'i') {
        (*big_ass_matrix)[offset2+i][offset2+i] = 1;
        (*constant)[offset2+i] = component_array[i].constant;
      }
    }
  }

void createBigAssMatrix(component *component_array,
  int component_array_length,
  int *node_array,
  int node_array_length,
  int ground,
  double ***big_ass_matrix,
  double **constant
) {
      int size = node_array_length - 1 + 2 * component_array_length;\
      *big_ass_matrix = createMatrix(size);
      *constant = createArray(size);
      for (int i = 0; i < size; i++) {
        (*constant)[i] = 0;
      }

      addMatrixA(component_array, component_array_length, node_array,
        node_array_length, ground, big_ass_matrix);

      addIdentity(node_array_length-1, component_array_length, big_ass_matrix);

      addBranch (component_array, component_array_length, node_array_length,
        big_ass_matrix, constant);
}

double* solveEquation(
  double **big_ass_matrix,
  double *constant_matrix,
  int size
) {
  double** inverse = adjoint(big_ass_matrix, size);
  double det = findDeterminant(big_ass_matrix, size);
  scalarMatrixMultiplication(1/det, size, &inverse);
  double *solved = matrixArrayMultiplication(inverse, constant_matrix, size);
  destroyMatrix(inverse);
  return solved;
}

void getInstance(
  component *component_array,
  int component_array_length,
  int ground,
  int *node_array,
  int node_array_length,
  double **instance,
  int *instance_length
) {

    double** big_ass_matrix;
    double* constant_matrix;
    createBigAssMatrix(component_array, component_array_length, node_array,
      node_array_length, ground, &big_ass_matrix, &constant_matrix);

    int size = node_array_length - 1 + component_array_length * 2;

    // printMatrix(big_ass_matrix, size);
    // printArray(constant_matrix, size);

    *instance = solveEquation(big_ass_matrix, constant_matrix, size);
    *instance_length = size;
}

void printInstance(
  double *instance,
  int instance_length,
  component *component_array,
  int component_array_length,
  int *node_array,
  int node_array_length,
  int ground
) {
  int groundPassed = 0;
  for (int i = 0; i < node_array_length; i++) {
    if (node_array[i] == ground) {
      groundPassed = 1;
      continue;
    }
      printf("node %d = %fV\n", node_array[i], instance[i - groundPassed]);
  }
  for (int i = 0; i < component_array_length; i++) {
    printf("component[%d] of type %c : %fV, %fA\n", i, component_array[i].type,
      instance[node_array_length + i -1],
      instance[node_array_length + component_array_length + i -1]);
  }
}
