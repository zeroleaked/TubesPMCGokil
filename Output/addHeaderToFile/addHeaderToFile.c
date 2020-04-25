#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../Configuration/configuration.h"
#include "../../Input/input.h"
#include "../output.h"

#define MAX_CHAR 255



int main(int argc, char *argv[]) {
  int ground;
  if (argc < 4) {
    printf("not enough arguments\n");
    return 1;
  }
  sscanf(argv[3], "%d", &ground);

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

  FILE *outfile = getCSVfile(argv[2]);
  addHeaderToFile(
    node_array,
    node_array_length,
    component_array,
    component_array_length,
    ground,
    &outfile
  );

  free(component_array);
  free(node_array);
}
