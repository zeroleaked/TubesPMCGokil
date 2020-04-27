#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../Configuration/configuration.h"
#include "../../Input/input.h"
#include "../output.h"

#define MAX_CHAR 1023

int main(int argc, char *argv[]) {
  int ground;
  double t;
  if (argc < 6) {
    printf("not enough arguments\n");
    return 1;
  }
  sscanf(argv[4], "%d", &ground);
  sscanf(argv[5], "%lf", &t);


  component *component_array;
  int component_array_length = 0;
  createComponentArrayFromFile(
    argv[1],
    1,
    &component_array,
    &component_array_length
  );

  int *node_array;
  int node_array_length = 0;
  createNodeArray(
    component_array,
    component_array_length,
    &node_array,
    &node_array_length
  );

  char line[MAX_CHAR];
  FILE *infile_solved = fopen(argv[2], "r");
  fgets(line, MAX_CHAR, infile_solved);

  double *solved_array = NULL;
  int solved_array_length = 0;

  char *ptr = line;
  int offset;
  double temp;
  while (sscanf(ptr, "%lf%n", &temp, &offset) == 1) {
    solved_array_length+=1;
    solved_array = realloc(solved_array, solved_array_length * sizeof(double));
    solved_array[solved_array_length-1] = temp;
    ptr += offset;
  }

  FILE *outfile = getCSVfile(argv[3]);
  addSolvedArrayToFile(
    t,
    solved_array,
    component_array,
    component_array_length,
    node_array,
    node_array_length,
    ground,
    &outfile
  );

  #ifdef DEBUG
  printf("ground = %d\n", ground);
  printComponents(component_array, component_array_length, 1);

  printf("solved_array:\n");
  for (int i = 0; i < solved_array_length; i++) {
    printf("%f ", solved_array[i]);
  }
  printf("\n");
  #endif

  fclose(outfile);
  free(component_array);
  free(node_array);
  free(solved_array);
}
