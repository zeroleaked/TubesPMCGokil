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


void addMatrixA(
  component *component_array,
  int component_array_length,
  int *node_array,
  int node_array_length,
  int ground,
  double ***tableau_matrix
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
          (*tableau_matrix)[j - groundPassed][col_offset + k] = -1;
          (*tableau_matrix)[row_offset + k][j - groundPassed] = -1;
        }
        else if (component_array[k].node2 == node_array[j]) {
          (*tableau_matrix)[j - groundPassed][col_offset + k] = 1;
          (*tableau_matrix)[row_offset + k][j - groundPassed] = 1;
        }
      }
    }

}

void addIdentity(int offset, int size, double ***tableau_matrix) {
  for (int i = 0; i < size; i++) {
    (*tableau_matrix)[offset+i][offset+i] = 1;
  }
}

void addBranch (
  component *component_array,
  int component_array_length,
  int node_array_length,
  double ***tableau_matrix,
  double **constant
) {
    int offset2 = node_array_length - 1 + component_array_length;
    int offset1 = node_array_length - 1;
    for (int i = 0; i < component_array_length; i++) {
      if ( component_array[i].type == 'R' ) {
        (*tableau_matrix)[offset2+i][offset1+i] = 1;
        (*tableau_matrix)[offset2+i][offset2+i] = -component_array[i].constant;
      }
      else if ( component_array[i].type == 'V' || component_array[i].type == 'v' ) {
        (*tableau_matrix)[offset2+i][offset1+i] = 1;
        (*constant)[offset2+i] = component_array[i].constant;
      }
      else if ( component_array[i].type == 'I' || component_array[i].type == 'i') {
        (*tableau_matrix)[offset2+i][offset2+i] = 1;
        (*constant)[offset2+i] = component_array[i].constant;
      }
    }
  }

void createTableauMatrices(
  component *component_array,
  int component_array_length,
  int *node_array,
  int node_array_length,
  int ground,
  double ***tableau_matrix,
  double **constant_array,
  int *tableau_length
) {
    *tableau_length = node_array_length - 1 + 2 * component_array_length;
    double **before_inverse_matrix = createMatrix(*tableau_length);
    *constant_array = createArray(*tableau_length);

    addMatrixA(component_array, component_array_length, node_array,
      node_array_length, ground, &before_inverse_matrix);

    addIdentity(node_array_length-1, component_array_length, &before_inverse_matrix);

    addBranch (
      component_array,
      component_array_length,
      node_array_length,
      &before_inverse_matrix,
      constant_array
    );

    createInverseMatrix( before_inverse_matrix, *tableau_length, tableau_matrix );
    destroyMatrix( &before_inverse_matrix );
}

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
      (*constant_array)[offset2+i] = component_array[i].constant;
    }
  }
};
