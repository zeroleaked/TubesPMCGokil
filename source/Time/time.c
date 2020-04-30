#include <stdio.h>
#include <math.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#include "../Configuration/configuration.h"
#include "../Tableau/tableau.h"
#include "../Output/output.h"
#include "../Matrices/matrices.h"

// mengubah atribut value pada komponen
void updateDynamicComponents(
  component *component_array,
  int component_array_length,
  wave *wave_array,
  double t,
  double *solved_array,
  int tableau_length
) {
  int wave_counter = 0;
  for (int i = 0; i < component_array_length; i++) {
    // capacitor
    if ( component_array[i].type == 'v' ) {
      component_array[i].value +=
        // tambah tegangan pada r dari model kapasitor
        solved_array[tableau_length - 2 * component_array_length + i + 1];
    } else
    // inductor
    if ( component_array[i].type == 'i' ) {
      component_array[i].value +=
        // tambah arus pada r dari model induktor
        solved_array[tableau_length - component_array_length + i + 1];
    } else
    if ( component_array[i].type == 'W' || component_array[i].type == 'J') {
      component_array[i].value =
        wave_array[wave_counter].amplitude * sin(
          2 * M_PI * wave_array[wave_counter].frequency * t
          + wave_array[wave_counter].shift
        );
      if (wave_array[wave_counter].type == 1) {
        if (component_array[i].value > 0)
          component_array[i].value = wave_array[wave_counter].amplitude;
        else
          component_array[i].value = -wave_array[wave_counter].amplitude;
      }
      wave_counter ++;
    }
  }
  #ifdef DEBUG
  printRawComponentArray(component_array, component_array_length);
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
  wave *wave_array,
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

  // membuat inversed_coefficient_matrix dan constant_array untuk dikalikan
  // nanti
  double** inversed_coefficient_matrix;
  double* constant_array;
  int tableau_length;
  createTableauMatrices(
    component_array,
    component_array_length,
    node_array,
    node_array_length,
    ground,
    &inversed_coefficient_matrix,
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
      inversed_coefficient_matrix,
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
      wave_array,
      t,
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
