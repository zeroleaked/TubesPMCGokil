#include "../Configuration/configuration.h"
#include "../Configuration/procedure.h" // ini yang bikin cycle includes
#include "../HashMap/hashMap.h"
#include "../Matrices/matrices.h"
#include "model.h"

void makeMatricesVoltage(koefisien_tab* circuit_node_coefficient,voltage_source_tab volt, node_tab node_circuit,
                         struct table *nodeNumInArrayPair){
    int i;
    int total_node = circuit_node_coefficient->total_node;

    int *isDone;
    isDone = (int*)calloc(total_node, sizeof(int));

    for (i = 0; i < volt.Neff; i++){
        voltage_source_t temp;
        temp = volt.array[i];
        int nodeNegInArray = lookup(nodeNumInArrayPair, temp.nodeNeg);
        int nodePosInArray = lookup(nodeNumInArrayPair, temp.nodePos);

        if (node_circuit.array[nodeNegInArray].isGround){
            if (!isDone[nodeNegInArray]){
                insertKoefisienTab(circuit_node_coefficient, nodeNegInArray, 1,-1,-1,0);
                isDone[nodeNegInArray] = 1;
            }
        }
        else if (node_circuit.array[nodePosInArray].isGround){
            if (!isDone[nodePosInArray]){
                insertKoefisienTab(circuit_node_coefficient, nodePosInArray, 1,-1,-1,0);
                isDone[nodeNegInArray] = 1;
            }
        }

        insertKoefisienTab(circuit_node_coefficient, nodeNegInArray,-1,
                nodePosInArray,1,temp.value);
    }
}

int findRow(double *row,double *ans,int* isDone,current_source_tab curr_list, resistor_tab res_list, voltage_source_tab volt_list,
            node_tab node_circuit,inductor_tab ind_list, capacitor_tab cap_list,  node_t node,struct table *nodeNumInArrayPair)
{
    int total_node = nodeNumInArrayPair->size;
    int i;

    voltage_source_t temp_vol;
    current_source_t temp_cur;

    if (node.isGround)
        return -1;
    for (i = 0; i < node.voltage_source_list.Neff; i++){
        temp_vol = volt_list.array[node.voltage_source_list.array[i]];
        int nodeNegInArray = lookup(nodeNumInArrayPair, temp_vol.nodeNeg);
        int nodePosInArray = lookup(nodeNumInArrayPair, temp_vol.nodePos);
        isDone[lookup(nodeNumInArrayPair, node.name)] = 1;
        if (node_circuit.array[nodeNegInArray].isGround || node_circuit.array[nodePosInArray].isGround)
            return -1;
        
        // super node
        if (node_circuit.array[nodeNegInArray].name != node.name){
            if (findRow(row, ans, isDone,curr_list, res_list, volt_list, node_circuit,
            ind_list, cap_list, node_circuit.array[nodeNegInArray],nodeNumInArrayPair) == -1){
                return -1;
            }
        }
        if (node_circuit.array[nodePosInArray].name != node.name){
            if (findRow(row, ans, isDone,curr_list, res_list, volt_list, node_circuit,
            ind_list, cap_list, node_circuit.array[nodePosInArray],nodeNumInArrayPair) == -1){
                return -1;
            }
        }
    }
    //-1 means ga bisa jadi supernode

    // current source kcl (masuk = positif)
    for (i = 0; i < node.current_source_list.Neff;i++){
        temp_cur = curr_list.array[(node.current_source_list.array)[i]];
        if (temp_cur.nodePos == node.name){
            (*ans) += temp_cur.value;
        }
        else{
            (*ans) -= temp_cur.value;
        }
    }

    // resistance arus keluar positif

    return 1;
}

void KCLAnalysisPerNode(koefisien_tab* circuit_node_coefficient,current_source_tab curr_list, resistor_tab res_list,
                        inductor_tab ind_list, capacitor_tab cap_list,  node_tab node_circuit,struct table *nodeNumInArrayPair)
{
    int total_node = circuit_node_coefficient->total_node;
    int i;
    int *isDone;
    isDone = (int*)calloc(total_node, sizeof(int));

    for (i = 0; i < total_node; i++){
        if (!isDone[i]){

        }
    }
}

