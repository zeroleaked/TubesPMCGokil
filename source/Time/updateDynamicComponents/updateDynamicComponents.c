#include <stdio.h>
#include <stdlib.h>

#include "../../Configuration/configuration.h"
#include "../../Input/input.h"
// #include "../../Matrices/matrices.h"
// #include "../../tableau.h"
#include "../time.h"

#define MAX_CHAR 255

int main() {
  int ground = 0;

  component *component_array;
  int component_array_length = 0;
  char path[MAX_CHAR] = "infile_component.txt";
  createComponentArrayFromFile(
    path,
    1,
    &component_array,
    &component_array_length
  );

  double *solved_array = NULL;
  int tableau_length = 0;
  FILE *infile = fopen("infile_solved.txt", "r");
  double temp;
  while (fscanf(infile,"%lf", &temp) == 1) {
    tableau_length ++;
    solved_array = realloc(solved_array, tableau_length * sizeof(double));
    solved_array[tableau_length-1] = temp;
  }

  updateDynamicComponents (
    component_array,
    component_array_length,
    solved_array,
    tableau_length
  );


  FILE *outfile = fopen("outfile.txt", "w");
  for (int i = 0; i < component_array_length; i++) {
    fprintf(outfile, "%f\n", component_array[i].value);
  }

  free(solved_array);
  free(component_array);
}
