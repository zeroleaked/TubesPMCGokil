#ifndef DEBUG_H
#define DEBUG_H

#include "configuration.h"
#include <stdio.h>

void printRes(resistor_t res){
    printf("Value = %f \n", res.value);
    printf("Node 1 = %d \n", res.node1);
    printf("Node 2 = %d \n", res.node2);
}

void printIn(inductor_t in){
    printf("Value = %f \n",        in.value);
    printf("Last Current = %f \n", in.last_curr);
    printf("Node 1 = %d \n",       in.node1);
    printf("Node 2 = %d \n",       in.node2);
}

void printCap(capacitor_t cap){
    printf("Value = %f \n",        cap.value);
    printf("Last Voltage = %f \n", cap.last_volt);
    printf("Node 1 = %d \n",       cap.node1);
    printf("Node 2 = %d \n",       cap.node2);
}

void printVoltageSource(voltage_source_t vol){
    printf("Value = %f \n",          vol.value);
    printf("Node Pos = %d \n",       vol.nodePos);
    printf("Node Neg = %d \n",       vol.nodeNeg);
}

void printCurrentSource(current_source_t cur){
    printf("Value = %f \n",          cur.value);
    printf("Node Pos = %d \n",       cur.nodePos);
    printf("Node Neg = %d \n",       cur.nodeNeg);
}

#endif