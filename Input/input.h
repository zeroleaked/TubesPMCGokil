#ifndef INPUT_H
#define INPUT_H

#include "stdio.h"
#include "../Configuration/configuration.h"
resistor_t askResistor(){
    resistor_t temp;
    printf("Masukkan nilai Resistor :");
    scanf("%lf", &(temp.value));
    printf("Masukkan node :");
    scanf("%d", &(temp.node1));
    printf("Masukkan node :");
    scanf("%d", &(temp.node2));
    return temp;  
}

capacitor_t askCapacitor(){
    capacitor_t temp;
    printf("Masukkan nilai Capacitor :");
    scanf("%lf", &(temp.value));
    printf("Masukkan node :");
    scanf("%d", &(temp.node1));
    printf("Masukkan node :");
    scanf("%d", &(temp.node2));
    printf("Masukkan nilai Tegangan saat t = t0 :");
    scanf("%lf", &(temp.last_volt));
    return temp;  
}

inductor_t askInductor(){
    inductor_t temp;
    printf("Masukkan nilai Induktor :");
    scanf("%lf", &(temp.value));
    printf("Masukkan node :");
    scanf("%d", &(temp.node1));
    printf("Masukkan node :");
    scanf("%d", &(temp.node2));
    printf("Masukkan nilai Arus saat t = t0 :");
    scanf("%lf", &(temp.last_curr));
    return temp;  
}

voltage_source_t askVoltageSource(){
    voltage_source_t temp;
    printf("Masukkan nilai Tegangan :");
    scanf("%lf", &(temp.value));
    printf("Masukkan nilai Node Positif :");
    scanf("%d", &(temp.nodePos));
    printf("Masukkan nilai Node Negatif :");
    scanf("%d", &(temp.nodeNeg));
    
    return temp;
}

current_source_t askCurrentSource(){
    current_source_t temp;
    printf("Masukkan nilai Arus :");
    scanf("%lf", &(temp.value));
    printf("Masukkan nilai Node Positif :");
    scanf("%d", &(temp.nodePos));
    printf("Masukkan nilai Node Negatif :");
    scanf("%d", &(temp.nodeNeg));

    return temp;
}

#endif