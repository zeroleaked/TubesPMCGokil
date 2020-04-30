#include <stdio.h>
#include <stdlib.h>

#include "../../Configuration/configuration.h"

#include "../../Input/input.h"
#include "../../Matrices/matrices.h"
#include "../tableau.h"

#define MAX_CHAR 255

int main(int argc, char *argv[]) {
  int ground;
  if (argc < 5) {
    printf("not enough arguments\n");
    return 1;
  }
  sscanf(argv[4], "%d", &ground);

  component *component_array;
  int component_array_length = 0;
  createComponentArrayFromFile(
    argv[1],
    1,
    &component_array,
    &component_array_length
  );

  int *node_array;
  int node_array_length = 0;
  createNodeArray(
    component_array,
    component_array_length,
    &node_array,
    &node_array_length
  );

  double **inversed_coefficient_matrix;
  double *constant_array;
  int tableau_length;
  createTableauMatrices(
    component_array,
    component_array_length,
    node_array,
    node_array_length,
    ground,
    &inversed_coefficient_matrix,
    &constant_array,
    &tableau_length
  );

  FILE *outfile = fopen(argv[2], "w");
  for (int i = 0; i < tableau_length; i++) {
    for (int j = 0; j < tableau_length; j++) {
      fprintf(outfile, "%f", inversed_coefficient_matrix[i][j]);
      if (j < tableau_length - 1) fprintf(outfile, ",");
    }
    fprintf(outfile, "\n");
  }
  fclose(outfile);


  outfile = fopen(argv[3], "w");
  for (int i = 0; i < tableau_length; i++) {
    fprintf(outfile, "%f\n", constant_array[i]);
  }

  destroyMatrix(&inversed_coefficient_matrix);
  free(constant_array);
  free(component_array);
  free(node_array);
}
