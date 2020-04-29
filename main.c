#include "Configuration/configuration.h"
#include "Input/input.h"
#include "Time/time.h"

#include <stdio.h>
#include <stdlib.h>

// -DDEBUG for debug

int main(){

  int ground = 0;
  double delta_t = 0.01;
  double t_start = 0;
  double t_stop  = 6;
  char *components_infile_path = "infiles/infile8.txt";
  char *outfile_path = "outfile.csv";

  component *component_array;
  int component_array_length = 0;
  wave *wave_array;
  createComponentArrayFromFile(
    components_infile_path,
    delta_t,
    &component_array,
    &component_array_length,
    &wave_array
  );
  printComponents(component_array, component_array_length, delta_t);

  int *node_array;
  int node_array_length = 0;
  createNodeArray(
    component_array,
    component_array_length,
    &node_array,
    &node_array_length
  );

  timeSeries(
    t_start,
    t_stop,
    delta_t,
    component_array,
    component_array_length,
    wave_array,
    node_array,
    node_array_length,
    ground,
    outfile_path
  );

  free(wave_array);
  destroyNodeArray(&node_array);
  destroyComponentArray(&component_array);

  return 0;
}
