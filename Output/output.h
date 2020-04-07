#ifndef OUTPUT_H
#define OUTPUT_H

FILE* getCSVfile(char *filepath);

void addSolvedArrayToFile(
  double t,
  double *solved_array,
  component *component_array,
  int component_array_length,
  int *node_array,
  int node_array_length,
  int ground,
  FILE **fptr
);

void addRawSolvedArrayToFile(double t, double *solved_array, int tableau_length, FILE **fptr);

void closeCSVfile(FILE **fptr);

void addHeaderToFile(
  int *node_array,
  int node_array_length,
  component *component_array,
  int component_array_length,
  int ground,
  FILE **fptr);

#endif
