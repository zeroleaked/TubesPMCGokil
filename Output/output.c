#include "../Configuration/configuration.h"
#include <stdio.h>

#ifdef DEBUG
void addRawSolvedArrayToFile(
  double t,
  double *solved_array,
  int tableau_length,
  FILE **fptr
) {
  fprintf(*fptr, "%f,", t);
  for (int i = 0; i < tableau_length; i++) {
    fprintf(*fptr, "%f,", solved_array[i]);
  }
  fprintf(*fptr, "\n");
}
#endif

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

void addNodeVoltagesToFile(
  double *solved_array,
  int *node_array,
  int node_array_length,
  int ground,
  FILE **fptr
) {
  int groundPassed = 0;
  for (int i = 0; i < node_array_length; i++) {
    if (node_array[i] == ground) {
      groundPassed = 1;
      continue;
    } else if (node_array[i] < 0) continue; // skip negative node
    fprintf(*fptr, "%f,", solved_array[i - groundPassed]);
  }
}

void addComponentVoltagesToFile(
  double *solved_array,
  component *component_array,
  int component_array_length,
  int offset,
  FILE **fptr
) {
  for (int i = 0; i < component_array_length; i++) {
    if ( component_array[i].type == 'v' ) {
      fprintf(*fptr, "%f,",
        solved_array[offset + i] + solved_array[offset + i + 1]);
      i++;
      continue;
    }
    else if ( component_array[i].type == 'i' ) {
      i++;
    }
    fprintf(*fptr, "%f,", solved_array[offset + i]);
  }
}

void addComponentCurrentsToFile(
  double *solved_array,
  component *component_array,
  int component_array_length,
  int offset,
  FILE **fptr
) {
  for (int i = 0; i < component_array_length; i++) {
    if ( component_array[i].type == 'i' ) {
      fprintf(*fptr, "%f,",
        solved_array[offset + i] + solved_array[offset + i + 1]);
      i++;
      continue;
    }
    else if ( component_array[i].type == 'v' ) {
      i++;
    }
    fprintf(*fptr, "%f,", solved_array[offset + i]);
  }
}

void addSolvedArrayToFile(
  double t,
  double *solved_array,
  component *component_array,
  int component_array_length,
  int *node_array,
  int node_array_length,
  int ground,
  FILE **fptr
) {
    fprintf(*fptr, "%f,", t);
    addNodeVoltagesToFile(solved_array, node_array, node_array_length, ground, fptr);
    addComponentVoltagesToFile(
      solved_array,
      component_array,
      component_array_length,
      node_array_length - 1,
      fptr
    );
    addComponentCurrentsToFile(
      solved_array,
      component_array,
      component_array_length,
      node_array_length + component_array_length - 1,
      fptr
    );
    fprintf(*fptr, "\n");
}

void closeCSVfile(FILE **fptr) {
  fclose(*fptr);
}
