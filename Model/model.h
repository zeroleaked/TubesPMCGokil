#ifndef MODEL_H
#define MODEL_H

void makeMatricesVoltage(koefisien_tab* circuit_node_coefficiet,voltage_source_tab volt, node_tab node_circuit,
                         struct table *nodeNumInArrayPair);

void KCLAnalysisPerNode(koefisien_tab* circuit_node_coefficient,voltage_source_tab volt_list,current_source_tab curr_list, resistor_tab res_list, 
                        inductor_tab ind_list, capacitor_tab cap_list,  node_tab node_circuit,struct table *nodeNumInArrayPair);

#endif