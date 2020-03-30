#ifndef PROCEDURE_H
#define PROCEDURE_H
// Initiation Tab. always use for initiate array of component
void initiateResTab(resistor_tab *tab);

void initiateInTab(inductor_tab *tab);

void initiateCapTab(capacitor_tab *tab);

void initiateVolTab(voltage_source_tab *tab);

void initiateCurTab(current_source_tab *tab);
void initiateListIntTab(list_int_tab *tab);

void initiateNodeTab(node_tab *tab);

// push component to array of component
void addResToTab(resistor_tab *tab , resistor_t res);

void addInToTab(inductor_tab *tab , inductor_t in);

void addCapToTab(capacitor_tab *tab , capacitor_t cap);

void addVolToTab(voltage_source_tab *tab , voltage_source_t vol);

void addCurToTab(current_source_tab *tab , current_source_t cur);

void addNodeToTab(node_tab *tab , node_t node);
void addIntegerToTab(list_int_tab *tab, int val);

// make Component
resistor_t makeRes(double value, int node1 , int node2);

inductor_t makeIn(double value, double last_cur, double node1, double node2);

capacitor_t makeCap(double value, double last_vol, double node1, double node2);

current_source_t makeCurr(double value, int nodePos, int nodeNeg);

voltage_source_t makeVolt(double value, int nodePos, int nodeNeg);

node_t makeNode(int node_name);

koefisien_tab makeKoefisienTab(int total_node);

void insertKoefisienTab(koefisien_tab *koef, int num1, double value1,
                        int num2, double value2, double answer);

void inserRowToKoefTab(koefisien_tab *koef, double *row,double ans);



#endif