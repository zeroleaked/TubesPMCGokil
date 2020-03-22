#ifndef VARIABLE_H
#define VARIABLE_H

#include "configuration.h"

/* Temporary variable */
resistor_t temp_resistor;
inductor_t temp_inductor;
capacitor_t temp_capacitor;
voltage_source_t temp_volt;
current_source_t temp_curr;

/* tab for Component */
resistor_tab resistor_list;
capacitor_tab capacitor_list;
inductor_tab inductor_list;
voltage_source_tab voltage_source_list;
current_source_tab current_source_list;


/* Total Rangkaian di Circuit */
node_tab node_circuit;

/*  Koefisien pada Matriks */
int **koefMatrices;

#endif