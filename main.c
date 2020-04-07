#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "Configuration/configuration.h"
#include "Input/input.h"
#include "Time/time.h"

// -DDEBUG for debug
// jangan nyalain debug kalo t di main() belom diatur. Restart komputer wkwk

int main(){

  int ground = 0;
  double delta_t = 0.001;
  double t_start = 0;
  double t_stop = 3;
  char *components_infile_path = "infiles/infile3.txt";
  char *outfile_path = "outfile.csv";

  component *component_array;
  int component_array_length = 0;
  component_array = NULL;
  createComponentArrayFromFile(
    components_infile_path,
    delta_t,
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

  simulateCircuit(
    t_start,
    t_stop,
    delta_t,
    component_array,
    component_array_length,
    node_array,
    node_array_length,
    ground,
    outfile_path
  );
  destroyNodeArray(&node_array);
  destroyComponentArray(&component_array);

  return 0;
}
