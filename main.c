#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "Matrices/matrices.h"
#include "Configuration/configuration.h"
#include "Tableau/tableau.h"
#include "Input/input.h"
#include "Time/time.h"
#include "Output/output.h"


int main(){
  component *component_array;
  component_array = NULL;

  int component_array_length = 0;
  int ground;
  double delta_t = 0.001;
  double t_start = 0;
  double t_stop = 3;

  getComponentsFromFile("Input/infile3.txt", &component_array, &component_array_length, delta_t);
  ground = 0;

  // printComponentArray(component_array, component_array_length);

  simulateCircuit(
    t_start,
    t_stop,
    delta_t,
    component_array,
    component_array_length,
    ground
  );

  return 0;
}
