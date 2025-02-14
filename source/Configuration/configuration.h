#ifndef CONFIGURATION_H

#define CONFIGURATION_H


typedef struct{
  char type;
  double value;
  int node1, node2;
} component;

typedef struct{
  int type;
  double amplitude, frequency, shift;
} wave;

void addComponent(
  component **component_array,
  int *length,
  char type,
  double constant,
  int node1,
  int node2
);

void addWave(
  wave **wave_array,
  int *length,
  int wave_type,
  double amplitude,
  double frequency,
  double shift
);

void initializeComponentArray(component **component_array);
void printComponents(component *component_array, int component_array_length,double delta_t);
void destroyComponentArray(component **component_array);

void createNodeArray(
  component *component_array,
  int component_array_length,
  int **node_array,
  int *node_array_length
);
void printNodeArray(int *node_array, int node_array_length);
void destroyNodeArray(int **node_array);

#ifdef DEBUG
void printRawComponentArray(component *component_array, int length);
#endif

#endif
