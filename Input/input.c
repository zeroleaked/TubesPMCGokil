#include <stdio.h>

#include "../Configuration/configuration.h"

void createComponentArrayFromFile(
  char *filepath,
  double delta_t,
  component **component_array,
  int *component_array_length
) {
  initializeComponentArray(component_array);

  FILE *fptr;
  fptr = fopen(filepath, "r");
  char type;
  double constant;
  int node1, node2;

  while (fscanf(fptr, " %c %lf %d %d", &type, &constant, &node1, &node2) == 4) {
    addComponent(component_array, component_array_length, type, constant, node1, node2, delta_t);
  }

  #ifdef DEBUG
  printComponentArray(*component_array, *component_array_length);
  #endif
}
