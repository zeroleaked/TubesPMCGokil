#ifndef VARIABLE_H
#define VARIABLE_H

#include "configuration.h"
#include "../HashMap/hashMap.h"

/* Temporary variable */
resistor_t temp_resistor;
inductor_t temp_inductor;
capacitor_t temp_capacitor;
voltage_source_t temp_voltage_source;
current_source_t temp_current_source;

/* tab for Component */
resistor_tab resistor_list;
capacitor_tab capacitor_list;
inductor_tab inductor_list;
voltage_source_tab voltage_source_list;
current_source_tab current_source_list;


/* Total Rangkaian di Circuit */
node_tab node_circuit;

/*  Koefisien pada Matriks */
koefisien_tab circuit_node_coefficient;

/* Time Simulation */
double time_start;
double time_end;
double time_now;
double time_sample;


/*  Urutan node pada Matriks dalam bentuk HashMap */
table *nodeNumInArrayPair;

/* Nilai Tegangan pada setiap node, urutan sesuai dengan urutan pada node */
double *voltage_in_node_now;

/* */
FILE *out;
#endif