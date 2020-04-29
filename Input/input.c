#include <stdio.h>
#include "../Configuration/configuration.h"
#include "input.h"

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
  double value;
  int node1, node2;
  int _negative_node = 0;

  while (fscanf(fptr, " %c %lf %d %d", &type, &value, &node1, &node2) == 4) {
    // membuat model resistif dari kapasitor. Bukan menambahkan kapasitor pada
    // component_array, melainkan sumber tegangan dan resistor.
    if (type == 'C') {
      _negative_node--;
      double initial_value;
      fscanf(fptr, "%lf", &initial_value);
      addComponent(component_array, component_array_length, 'v', initial_value,
        node1, _negative_node);
      addComponent(component_array, component_array_length, 'R', delta_t/value,
        _negative_node, node2);
    }
    else if (type == 'L') {
      double initial_value;
      fscanf(fptr, "%lf", &initial_value);
      // membuat model resistif dari induktor. Bukan menambahkan induktor pada
      // component_array, melainkan sumber arus dan resistor.
      addComponent(component_array, component_array_length, 'i', initial_value,
        node1, node2);
      addComponent(component_array, component_array_length, 'R', value/delta_t,
        node1, node2);
      return;
    }
    else {
      addComponent(component_array, component_array_length, type, value, node1, node2);
    }
  }

  #ifdef DEBUG
  printRawComponentArray(*component_array, *component_array_length);
  #endif
}
