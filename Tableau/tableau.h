#ifndef TABLEAU_H
#define TABLEAU_H

void createTableauMatrices(
  component *component_array,
  int component_array_length,
  int *node_array,
  int node_array_length,
  int ground,
  double ***tableau_matrix,
  double **constant_array,
  int *tableau_length
);

void updateConstantArray (
  component *component_array,
  int component_array_length,
  double **constant_array,
  int tableau_length
);

void createSolvedArray(
  double **tableau_matrix,
  double *constant_array,
  int tableau_length,
  double **solved_array
);

void createInstance(
  component *component_array,
  int component_array_length,
  int ground,
  int *node_array,
  int node_array_length,
  double **solved_array,
  int *tableau_length
);

void printSolvedArray(
  double *solved_array,
  int tableau_length,
  component *component_array,
  int component_array_length,
  int *node_array,
  int node_array_length,
  int ground
);


#endif
