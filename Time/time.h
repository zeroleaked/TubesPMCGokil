#ifndef TIME_H
#define TIME_H

void simulateCircuit(
  double t_start,
  double t_stop,
  double delta_t,
  component *component_array,
  int component_array_length,
  int *node_array,
  int node_array_length,
  int ground,
  char *outfile_path
);

#endif
