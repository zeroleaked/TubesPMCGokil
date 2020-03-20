#ifndef INPUT_H
#define INPUT_H

#include "configuration.h"
#include "stdio.h"
resistor_t askResistor(){
    resistor_t temp;
    printf("Masukkan nilai Resistor ");
    scanf("%f", &(temp.value));
    printf("Masukkan node :");
    scanf("%d", &(temp.node1));
    printf("Masukkan node :");
    scanf("%d", &(temp.node2));    
}

#endif