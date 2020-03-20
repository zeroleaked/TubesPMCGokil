#ifndef CONFIGURATION_H
#define CONFIGURATION_H

typedef struct{
    double value;
    int node1, node2;
}resistor_t;

typedef struct{
    double value;
    double last_curr;
    int node1, node2;
}inductor_t;

typedef struct{
    double value;
    double last_volt;
    int node1, node2;
}capacitor_t;

typedef struct{
    double value;
    int nodePos, nodeNeg;
}voltage_t, current_t;

typedef struct{
    resistor_t *array;
    int Neff;
}resistor_tab;

typedef struct {
    capacitor_t *array;
    int Neff;
} capacitor_tab;

typedef struct {
    inductor_t *array;
    int Neff;
}inductor_tab;

typedef struct{
    voltage_t *array;
    int Neff;
}voltage_tab;

typedef struct{
    current_t *array;
    int Neff;
}current_tab;

#endif


