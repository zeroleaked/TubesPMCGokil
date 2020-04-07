#include "../Configuration/configuration.h"
#include <stdio.h>

FILE* getCSVfile(char *filepath) {
  FILE *fptr;
  fptr = fopen(filepath, "w");
  return fptr;
}

void addHeaderToFile(
  int *node_array,
  int node_array_length,
  component *component_array,
  int component_array_length,
  int ground,
  FILE **fptr
) {
  fprintf(*fptr, "t,");
  for (int i = 0; i < node_array_length; i++) {
    if (node_array[i] != ground && node_array[i] > 0)
      fprintf(*fptr, "node %d (Volt),", node_array[i]);
  }
  for (int i = 0; i < component_array_length; i++) {
    if ( component_array[i].type == 'v') {
      fprintf(*fptr, "V(C) (Volt),");
      i++;
      continue;
    } else if ( component_array[i].type == 'i' ) {
      fprintf(*fptr, "V(L) (Volt),");
      i++;
      continue;
    }
    fprintf(*fptr, "V(%c) (Volt),", component_array[i].type);
  }
  for (int i = 0; i < component_array_length; i++) {
    if ( component_array[i].type == 'v') {
      fprintf(*fptr, "I(C) (Amp),");
      i++;
      continue;
    } else if ( component_array[i].type == 'i') {
      fprintf(*fptr, "I(L) (Amp),");
      i++;
      continue;
    }
    fprintf(*fptr, "I(%c) (Amp),", component_array[i].type);
  }
  fprintf(*fptr, "\n");
}

void addSummedInstanceToFile(
  double t,
  double *instance,
  component *component_array,
  int component_array_length,
  int *node_array,
  int node_array_length,
  int ground,
  FILE **fptr
) {
    fprintf(*fptr, "%f,", t);
    // print nodes
    int groundPassed = 0;
    for (int i = 0; i < node_array_length; i++) {
      if (node_array[i] == ground) {
        groundPassed = 1;
        continue;
      } else if (node_array[i] < 0) continue; // skip negative node
      fprintf(*fptr, "%f,", instance[i - groundPassed]);
    }

    // print voltages and currents
    for (int i = 0; i < 2*component_array_length; i++) {
      // capacitor case
      if ( component_array[i % component_array_length].type == 'v') {
        if ( i < component_array_length ) {
          // voltage
          fprintf(*fptr, "%f,", instance[node_array_length + i -1] + instance[node_array_length + i]);
        } else {
          // current
          fprintf(*fptr, "%f,", instance[node_array_length + i -1]);
        }
        i++;
      } else if ( component_array[i % component_array_length].type == 'i') {
        if ( i < component_array_length ) {
          // voltage
          fprintf(*fptr, "%f,", instance[node_array_length + i -1]);
        } else {
          // current
          fprintf(*fptr, "%f,", instance[node_array_length + i -1] + instance[node_array_length + i]);
        }
        i++;
      } else
      fprintf(*fptr, "%f,", instance[node_array_length + i -1]);
    }
    fprintf(*fptr, "\n");
}

void addInstanceToFile(double t, double *instance, int instance_length, FILE **fptr) {
  fprintf(*fptr, "%f,", t);
  for (int i = 0; i < instance_length; i++) {
    fprintf(*fptr, "%f,", instance[i]);
  }
  fprintf(*fptr, "\n");
}

void closeCSVfile(FILE **fptr) {
  fclose(*fptr);
}

// void addHeaderToFile(
//   double *node_array,
//   int node_array_length,
//   component *component_array,
//   int component_array_length,
//   int ground,
//   FILE **fptr) {
//     for (int i = 0; i <)
//   }
