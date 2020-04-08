#ifndef TABLEAU_H
#define TABLEAU_H

void createTableauMatrices(
  component *component_array,
  int component_array_length,
  int *node_array,
  int node_array_length,
  int ground,
  double ***inversed_coefficient_matrix,
  double **constant_array,
  int *tableau_length
);

void updateConstantArray (
  component *component_array,
  int component_array_length,
  double **constant_array,
  int tableau_length
);

#ifdef DEBUG
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

#endif
