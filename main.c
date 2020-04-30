#include "Configuration/configuration.h"
#include "Input/input.h"
#include "Time/time.h"

#include <stdio.h>
#include <stdlib.h>

// -DDEBUG for debug

int main(){
  int ground;
  // double delta_t = 1e-4;
  double t_start;
  double t_stop;
  // char *components_infile_path = "infiles/infile8.txt";
  char *components_infile_path = "infile.txt";
  char *time_infile_path = "timefile.txt";
  char *ground_infile_path = "groundfile.txt";
  char *outfile_path = "outfile.csv";
  printf("start reading\n");


  addTimeFromFile(time_infile_path, &t_start, &t_stop);
  printf("start = %fs, end = %fs\n", t_start, t_stop);
  addGroundFromFile(ground_infile_path, &ground);
  printf("ground = %d\n", ground);

  double delta_t = (t_stop-t_start) * 1e-5;

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
