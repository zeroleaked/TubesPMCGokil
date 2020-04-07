
#include <stdio.h>
#include <stdlib.h>

#include "../Configuration/configuration.h"
#include "../Tableau/tableau.h"
#include "../Output/output.h"


// jangan nyalain debug kalo t di main() belom diatur. Restart komputer wkwk
// #define DEBUG

void updateCapacitorsInductors(
  component *component_array,
  int component_array_length,
  double *instance,
  int instance_length,
  int *node_array,
  int node_array_length
) {
  for (int i = 0; i < component_array_length; i++) {
    if ( component_array[i].type == 'v' ) {
      // printf("v sebelum = %fV, r = %fV\n", component_array[i].constant, instance[node_array_length + i]);
      component_array[i].constant += instance[node_array_length + i];
    } else if ( component_array[i].type == 'i' ) {
      // printf("i sebelum = %fA, r = %fA\n", component_array[i].constant, instance[node_array_length + component_array_length + i]);
      component_array[i].constant += instance[node_array_length + component_array_length + i];
    }
  }
}

void simulateCircuit(
  double t_start,
  double t_stop,
  double delta_t,
  component *component_array,
  int component_array_length,
  int ground
) {

  int *node_array;
  int node_array_length = 0;
  getNodeArray(
    component_array,
    component_array_length,
    &node_array,
    &node_array_length
  );

  FILE *outfile;
  outfile = getCSVfile("output.csv");
  addHeaderToFile(
    node_array,
    node_array_length,
    component_array,
    component_array_length,
    ground,
    &outfile
  );

  double* instance;
  int instance_length;

  double t = 0;
  while (t < t_stop) {
    #ifdef DEBUG
    printf("--------------------\n");
    printf("t=%f\n", t);
    #endif

    getInstance(
      component_array, //dynamic
      component_array_length, //static
      ground, //static
      node_array, //static
      node_array_length, //static
      &instance, //dynamic
      &instance_length //dynamic
    );

    #ifdef DEBUG
    printInstance(
      instance,
      instance_length,
      component_array,
      component_array_length,
      node_array,
      node_array_length,
      ground
    );
    #endif

    if (t >= t_start)
      addSummedInstanceToFile(
        t,
        instance,
        component_array,
        component_array_length,
        node_array,
        node_array_length,
        ground,
        &outfile
      );

    updateCapacitorsInductors(
      component_array,
      component_array_length,
      instance,
      instance_length,
      node_array,
      node_array_length
    );

    #ifdef DEBUG
    printComponentArray(component_array, component_array_length);
    #endif

    t += delta_t;
    free(instance);
  }
  closeCSVfile(outfile);
  free(node_array);
  free(component_array);
}
