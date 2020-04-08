#ifdef DEBUG
#include <stdio.h>
#endif

#include "../Configuration/configuration.h"
#include "../Matrices/matrices.h"


#ifdef DEBUG
void printSolvedArray(
  double *solved_array,
  int tableau_length,
  component *component_array,
  int component_array_length,
  int *node_array,
  int node_array_length,
  int ground
) {
  printf("\ninstance:\n");
  int groundPassed = 0;
  for (int i = 0; i < node_array_length; i++) {
    if (node_array[i] == ground) {
      groundPassed = 1;
      continue;
    }
      printf("node %d = %fV\n", node_array[i], solved_array[i - groundPassed]);
  }
  for (int i = 0; i < component_array_length; i++) {
    printf("component[%d] of type %c : %fV, %fA\n", i, component_array[i].type,
      solved_array[node_array_length + i -1],
      solved_array[node_array_length + component_array_length + i -1]);
  }
  printf("\n");
}
#endif

// menambahkan persamaan KCL pada inversed_coefficient_matrix
void addMatrixA(
  component *component_array,
  int component_array_length,
  int *node_array,
  int node_array_length,
  int ground,
  double ***inversed_coefficient_matrix
) {
    // untuk A
    int col_offset = node_array_length - 1 + component_array_length;
    // untuk A transpose
    int row_offset = node_array_length - 1;

    int groundPassed = 0;

    for (int j = 0; j < node_array_length; j++) {
      if (ground == node_array[j]) {
        groundPassed = 1;
        continue;
      }
      // cari komponen yang terhubung dengan node j
      for (int k = 0; k < component_array_length; k++) {
        if (component_array[k].node1 == node_array[j]) {
          (*inversed_coefficient_matrix)[j - groundPassed][col_offset + k] = -1;
          (*inversed_coefficient_matrix)[row_offset + k][j - groundPassed] = -1;
        }
        else if (component_array[k].node2 == node_array[j]) {
          (*inversed_coefficient_matrix)[j - groundPassed][col_offset + k] = 1;
          (*inversed_coefficient_matrix)[row_offset + k][j - groundPassed] = 1;
        }
      }
    }

}

// menambahkan matriks identitas pada inversed_coefficient_matrix
void addIdentity(int offset, int size, double ***inversed_coefficient_matrix) {
  for (int i = 0; i < size; i++) {
    (*inversed_coefficient_matrix)[offset+i][offset+i] = 1;
  }
}

// menambahkan persamaan branch pada inversed_coefficient_matrix dan
// constant_array
void addBranch (
  component *component_array,
  int component_array_length,
  int node_array_length,
  double ***inversed_coefficient_matrix,
  double **constant
) {
    // offset untuk akses col M
    int offset1 = node_array_length - 1;
    // offset untuk akses row M, row N, col N
    int offset2 = node_array_length - 1 + component_array_length;
    for (int i = 0; i < component_array_length; i++) {
      if ( component_array[i].type == 'R' ) {
        // masukkan ke matriks M
        (*inversed_coefficient_matrix)[offset2+i][offset1+i] = 1;
        // masukkan ke matriks N
        (*inversed_coefficient_matrix)[offset2+i][offset2+i] = -component_array[i].value;
      }
      else if ( component_array[i].type == 'V' || component_array[i].type == 'v' ) {
        // masukkan ke matriks M
        (*inversed_coefficient_matrix)[offset2+i][offset1+i] = 1;
        // masukkan ke u
        (*constant)[offset2+i] = component_array[i].value;
      }
      else if ( component_array[i].type == 'I' || component_array[i].type == 'i') {
        // masukkan ke N
        (*inversed_coefficient_matrix)[offset2+i][offset2+i] = 1;
        // masukkan ke u
        (*constant)[offset2+i] = component_array[i].value;
      }
    }
  }

// mengalokasikan dan mengisi memori untuk inversed_coefficient_matrix dan
// constant_array
void createTableauMatrices(
  component *component_array,
  int component_array_length,
  int *node_array,
  int node_array_length,
  int ground,
  double ***inversed_coefficient_matrix,
  double **constant_array,
  int *tableau_length
) {
  *tableau_length = node_array_length - 1 + 2 * component_array_length;

  double **coefficient_matrix = createMatrix(*tableau_length);
  *constant_array = createArray(*tableau_length);

  // populate
  addMatrixA(component_array, component_array_length, node_array,
    node_array_length, ground, &coefficient_matrix);
  addIdentity(
    node_array_length - 1,
    component_array_length,
    &coefficient_matrix
  );
  addBranch (
    component_array,
    component_array_length,
    node_array_length,
    &coefficient_matrix,
    constant_array
  );
  // inverse matriks koefisien
  createInverseMatrix(coefficient_matrix, *tableau_length, inversed_coefficient_matrix);
  destroyMatrix( &coefficient_matrix );
}

// memperbarui persamaan branch pada constant_array berdasarkan value sumber
// arus dan sumber tegangan pada component_array
void updateConstantArray (
  component *component_array,
  int component_array_length,
  double **constant_array,
  int tableau_length
) {
  int offset1 = tableau_length - 2 * component_array_length;
  int offset2 = tableau_length - component_array_length;
  for (int i = 0; i < component_array_length; i++) {
    if ( component_array[i].type == 'v' || component_array[i].type == 'i' ) {
      (*constant_array)[offset2+i] = component_array[i].value;
    }
  }
};
