#ifndef OUTPUT_H
#define OUTPUT_H
FILE* getCSVfile(char *filepath);

void addSummedInstanceToFile(
  double t,
  double *instance,
  component *component_array,
  int component_array_length,
  int *node_array,
  int node_array_length,
  int ground,
  FILE **fptr
);

void addInstanceToFile(double t, double *instance, int instance_length, FILE **fptr);

void closeCSVfile(FILE *fptr);

void addHeaderToFile(
  int *node_array,
  int node_array_length,
  component *component_array,
  int component_array_length,
  int ground,
  FILE **fptr);

#endif