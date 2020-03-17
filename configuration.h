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

#endif


