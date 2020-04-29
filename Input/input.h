#ifndef INPUT_H
#define INPUT_H

void createComponentArrayFromFile(
  char *filename,
  double delta_t,
  component **component_array,
  int *component_array_length,
  wave **wave_array
);

#endif
