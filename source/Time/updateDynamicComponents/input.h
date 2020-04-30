#ifndef INPUT_H
#define INPUT_H

void addTimeFromFile(
    char *filepath,
    double *time_start,
    double *time_end
  );

void addGroundFromFile(
    char *filepath,
    int *ground
  );

void createComponentArrayFromFile(
  char *filename,
  double delta_t,
  component **component_array,
  int *component_array_length,
  wave **wave_array
);

#endif
