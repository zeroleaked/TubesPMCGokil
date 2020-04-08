#include <stdlib.h>


#include <stdio.h>

#include "configuration.h"



void printComponents(component *component_array, int length, int delta_t) {
  int vsource = 1, csource = 1, resistor = 1, capacitor = 1, inductor = 1;
  printf("\nName\tValue\t\tNode1\tNode2\n");
  for (int i = 0; i < length; i++) {
    if (component_array[i].type == 'V') {
      printf("V%d\t%.3e V\t%d\t%d\n", vsource++, component_array[i].value,
        component_array[i].node1, component_array[i].node2);
    } else
    if (component_array[i].type == 'I') {
      printf("I%d\t%.3e A\t%d\t%d\n", csource++, component_array[i].value,
        component_array[i].node1, component_array[i].node2);
    } else
    if (component_array[i].type == 'R') {
      printf("R%d\t%.3e Ohm\t%d\t%d\n", resistor++, component_array[i].value,
        component_array[i].node1, component_array[i].node2);
    } else
    if (component_array[i].type == 'v') {
      printf("C%d\t%.3e F\t%d\t%d\n", capacitor++, delta_t/component_array[i+1].value,
        component_array[i].node1, component_array[i+1].node2);
      i++;
    } else
    if (component_array[i].type == 'i') {
      printf("L%d\t%.3e H\t%d\t%d\n", capacitor++, delta_t*component_array[i+1].value,
        component_array[i].node1, component_array[i].node2);
      i++;
    }
  }
  printf("\n");
}

#ifdef DEBUG
void printRawComponentArray(component *component_array, int length) {
  printf("component_array:\n");
  for (int i = 0; i < length; i++) {
    printf("%c %d %d %f\n", component_array[i].type, component_array[i].node1, component_array[i].node2, component_array[i].value);
  }
  printf("\n");
}

void printNodeArray(int *node_array, int node_array_length) {
  printf("node_array:\n");
  for (int i = 0; i < node_array_length; i++) {
    printf("%d ", node_array[i]);
  }
  printf("\n");
}
#endif

// acuan nama untuk node tambahan (yang tidak diinput, tapi diperlukan untuk
// analisis)
int _negative_node = 0;

// tambah komponen ke component_array
void addComponent(
  component **component_array,
  int *length,
  char type,
  double value,
  int node1,
  int node2,
  double delta_t
) {

  if (type == 'C') {
    // membuat model resistif dari kapasitor. Bukan menambahkan kapasitor pada
    // component_array, melainkan sumber tegangan dan resistor. Untuk ke depannya,
    // v bisa diberikan angka selain 0 (kapasitor memiliki tegangan awal)
    _negative_node --;
    addComponent(component_array, length, 'v', 0, node1, _negative_node, 0);
    addComponent(component_array, length, 'R', delta_t/value, _negative_node, node2, 0);
    return;
  } else if (type == 'L') {
    // membuat model resistif dari induktor. Bukan menambahkan induktor pada
    // component_array, melainkan sumber arus dan resistor. Untuk ke depannya,
    // i bisa diberikan angka selain 0 (induktor memiliki arus awal)
    addComponent(component_array, length, 'i', 0, node1, node2, 0);
    addComponent(component_array, length, 'R', value/delta_t, node1, node2, 0);
    return;
  }

  *length += 1;
  *component_array = realloc(*component_array, *length * sizeof(component));

  (*component_array)[*length-1].type = type;
  (*component_array)[*length-1].value = value;
  (*component_array)[*length-1].node1 = node1;
  (*component_array)[*length-1].node2 = node2;
}

void initializeComponentArray(component **component_array) {
  *component_array = NULL;
}

void destroyComponentArray(component **component_array) {
  free(*component_array);
}

// mendaftarkan semua node yang ada pada component_array
void createNodeArray(
  component *component_array,
  int component_array_length,
  int **node_array,
  int *node_array_length
) {
  *node_array = NULL;

  int length = 0;
  for (int i = 0; i < component_array_length; i++) {
    // cek apabila node1 atau node2 sudah ditambahkan ke node_array
    int found1 = 0, found2 = 0;

    for (int j = 0; j < *node_array_length; j++) {
      if ( component_array[i].node1 == (*node_array)[j]) {
        found1 = 1;
      }
      if ( component_array[i].node2 == (*node_array)[j]) {
        found2 = 1;
      }
      if (found1 && found2) break;
    }

    // jika tidak ada, tambahkan
    if (!found1) {
      *node_array_length += 1;
      *node_array = realloc(*node_array, *node_array_length * sizeof(int));
      (*node_array)[*node_array_length-1] = component_array[i].node1;
    }
    if (!found2) {
      *node_array_length += 1;
      *node_array = realloc(*node_array, *node_array_length * sizeof(int));
      (*node_array)[*node_array_length-1] = component_array[i].node2;
    }

    found1 = found2 = 0;
  }

  #ifdef DEBUG
  printNodeArray(*node_array, *node_array_length);
  #endif
}

void destroyNodeArray(int **node_array) {
  free(*node_array);
}
