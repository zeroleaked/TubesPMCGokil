#include <stdio.h>
#include <stdlib.h>

#include "../../Configuration/configuration.h"

#include "../../Input/input.h"
#include "../../Matrices/matrices.h"
#include "../tableau.h"

#define MAX_CHAR 255

int main(int argc, char *argv[]) {
  int ground;
  if (argc < 5) {
    printf("not enough arguments\n");
    return 1;
  }
  sscanf(argv[4], "%d", &ground);

  component *component_array;
  int component_array_length = 0;
  createComponentArrayFromFile(
    argv[1],
    1,
    &component_array,
    &component_array_length
  );

  double *constant_array = NULL;
  int tableau_length = 0;
  FILE *infile = fopen(argv[2], "r");
  double temp;
  while (fscanf(infile,"%lf", &temp) == 1) {
    tableau_length ++;
    constant_array = realloc(constant_array, tableau_length * sizeof(double));
    constant_array[tableau_length-1] = temp;
  }

  // printf("before\n");
  // for (int i = 0; i < tableau_length; i++) {
  //   printf("%f ", constant_array[i]);
  // }
  // printf("\n");

  updateConstantArray (
    component_array,
    component_array_length,
    &constant_array,
    tableau_length
  );

  // printf("after\n");
  // for (int i = 0; i < tableau_length; i++) {
  //   printf("%f ", constant_array[i]);
  // }
  // printf("\n");

  FILE *outfile = fopen(argv[3], "w");
  for (int i = 0; i < tableau_length; i++) {
    fprintf(outfile, "%f\n", constant_array[i]);
  }

  free(constant_array);
  free(component_array);
}
