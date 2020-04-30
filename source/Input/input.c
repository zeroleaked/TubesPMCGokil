#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#include "../Configuration/configuration.h"
#include "input.h"

void addTimeFromFile(
    char *filepath,
    double *time_start,
    double *time_end)
{
    FILE *fptr;
    fptr = fopen(filepath, "r");

    if(fptr == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    while(fscanf(fptr, "%lf %lf", time_start, time_end)!=2);
}

void addGroundFromFile(
    char *filepath,
    int *ground
  ) {
      FILE *fptr;
      fptr = fopen(filepath, "r");

      if(fptr == NULL)
      {
          printf("Error opening file\n");
          exit(1);
      }

      while(fscanf(fptr, "%d", ground)!=1);
  }


void createComponentArrayFromFile(
  char *filepath,
  double delta_t,
  component **component_array,
  int *component_array_length,
  wave **wave_array
) {
  initializeComponentArray(component_array);
  *wave_array = NULL;
  int wave_array_length = 0;

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
    }
    else if (type == 'W' || type == 'J') {
      int wave_type;
      double frequency;
      double shift;
      double initial_value = sin((0+shift) * M_PI / 180);
      fscanf(fptr, "%d %lf %lf", &wave_type, &frequency, &shift);
      double time_shift = shift * frequency * 2 * M_PI;
      addComponent(component_array, component_array_length, type, sin(time_shift),
        node1, node2);
      addWave(wave_array, &wave_array_length, wave_type, value, frequency, time_shift);
    }
    else {
      addComponent(component_array, component_array_length, type, value, node1, node2);
    }
  }

  #ifdef DEBUG
  printRawComponentArray(*component_array, *component_array_length);
  #endif
}
