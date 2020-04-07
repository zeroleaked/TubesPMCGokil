#include <stdio.h>

#include "../Configuration/configuration.h"
#include "../Tableau/tableau.h"
#include "../Output/output.h"
#include "../Matrices/matrices.h"

// mengubah atribut value pada komponen
void updateDynamicComponents(
  component *component_array,
  int component_array_length,
  double *solved_array,
  int tableau_length
) {
  for (int i = 0; i < component_array_length; i++) {
    // capacitor
    if ( component_array[i].type == 'v' ) {
      component_array[i].value +=
        // tambah tegangan pada r dari model kapasitor
        solved_array[tableau_length + 1 - 2 * component_array_length + i];
    } else
    // inductor
    if ( component_array[i].type == 'i' ) {
      component_array[i].value +=
        // tambah arus pada r dari model induktor
        solved_array[tableau_length + 1 - component_array_length + i];
    }
  }
  #ifdef DEBUG
  printComponentArray(component_array, component_array_length);
  #endif
}

// simulasi component_array dengan perubahan terhadap waktu, output
// langsung ditulis ke file
void timeSeries(
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

  // buat tableau_matrix untuk dikalikan
  double** tableau_matrix;
  double* constant_array;
  int tableau_length;
  createTableauMatrices(
    component_array,
    component_array_length,
    node_array,
    node_array_length,
    ground,
    &tableau_matrix,
    &constant_array,
    &tableau_length
  );

  double* solved_array;
  double t = 0;
  while (t < t_stop) {
    #ifdef DEBUG
    printf("--------------------\n");
    printf("\nt = %fs\n", t);
    #endif

    solved_array = matrixArrayMultiplication(
      tableau_matrix,
      constant_array,
      tableau_length
    );

    #ifdef DEBUG
    printSolvedArray(
      solved_array,
      tableau_length,
      component_array,
      component_array_length,
      node_array,
      node_array_length,
      ground
    );
    #endif

    if (t >= t_start)
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

    // ubah value pada komponen
    updateDynamicComponents(
      component_array,
      component_array_length,
      solved_array,
      tableau_length
    );

    // implikasi dari pengubahan value pada sumber tegangan dan sumber arus,
    // persamaan branch berubah
    updateConstantArray (
      component_array,
      component_array_length,
      &constant_array,
      tableau_length
    );

    t += delta_t;

    // hasil sudah tidak diperlukan lagi
    destroyArray(&solved_array);
  }
  closeCSVfile(&outfile);
}
