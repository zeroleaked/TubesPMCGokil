#ifndef TIME_H
#define TIME_H

void timeSeries(
  double t_start,
  double t_stop,
  double delta_t,
  component *component_array,
  int component_array_length,
  wave *wave_array,
  int *node_array,
  int node_array_length,
  int ground,
  char *outfile_path
);

void updateDynamicComponents(
  component *component_array,
  int component_array_length,
  wave *wave_array,
  double t,
  double *solved_array,
  int tableau_length
);

#endif
