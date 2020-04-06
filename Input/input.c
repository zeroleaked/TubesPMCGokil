#include "../Configuration/configuration.h"
#include <stdio.h>

void getComponentsFromFile(
  char *filepath,
  component **component_array,
  int *component_array_length,
  double delta_t
) {

  FILE *fptr;
  fptr = fopen(filepath, "r");
  char type;
  double constant;
  int node1, node2;

  while (fscanf(fptr, " %c %lf %d %d", &type, &constant, &node1, &node2) == 4) {
    addComponent(component_array, component_array_length, type, constant, node1, node2, delta_t);
  }
  // printComponentArray(*component_array, *component_array_length);
}
