#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#define SMALLEST_TIME_SAMPLING 0.000001
#define BIGGEST_TIME_SAMPLING 0.5

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
}voltage_source_t, current_source_t;

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
    voltage_source_t *array;
    int Neff;
}voltage_source_tab;


typedef struct{
    current_source_t *array;
    int Neff;
}current_source_tab;

typedef struct{
    int *array;
    int Neff;
}list_int_tab;

typedef struct {
    double **array_koef;
    double *ans;
    int Neff;
    int total_node;
}koefisien_tab;


typedef struct{
    int name;
    list_int_tab res_list;
    list_int_tab ind_list;
    list_int_tab cap_list;
    list_int_tab current_source_list;
    list_int_tab voltage_source_list;
    int isGround;
}node_t;

typedef struct {
    node_t *array;
    int Neff;
}node_tab;


#endif