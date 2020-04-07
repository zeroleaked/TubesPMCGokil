#include <stdio.h>

#include "../Configuration/configuration.h"
#include "../Tableau/tableau.h"
#include "../Output/output.h"

void updateDynamicComponents(
  component *component_array,
  int component_array_length,
  double *instance,
  int instance_length
) {
  for (int i = 0; i < component_array_length; i++) {
    // capacitor
    if ( component_array[i].type == 'v' ) {
      component_array[i].constant +=
        instance[instance_length + 1 - 2 * component_array_length + i];
    } else
    // inductor
    if ( component_array[i].type == 'i' ) {
      component_array[i].constant +=
        instance[instance_length + 1 - component_array_length + i];
    }
  }
  #ifdef DEBUG
  printComponentArray(component_array, component_array_length);
  #endif
}

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
) {
  FILE *outfile;
  outfile = getCSVfile(outfile_path);

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
    printf("\nt = %fs\n", t);
    #endif

    createInstance(
      component_array,
      component_array_length,
      ground,
      node_array,
      node_array_length,
      &instance,
      &instance_length
    );

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

    updateDynamicComponents(
      component_array,
      component_array_length,
      instance,
      instance_length
    );

    t += delta_t;

    destroyInstance(&instance);
  }
  closeCSVfile(&outfile);
}
