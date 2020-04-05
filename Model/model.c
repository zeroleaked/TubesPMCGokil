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

    for (i = 0; i < node_circuit.Neff; i++){
        if ((node_circuit.array)[i].isGround){
            insertKoefisienTab(circuit_node_coefficient, lookup(nodeNumInArrayPair,(node_circuit.array[i]).name), 1, -1 , -1, 0);
            
        }
    }

    for (i = 0; i < volt.Neff; i++){
        voltage_source_t temp;
        temp = volt.array[i];
        int nodeNegInArray = lookup(nodeNumInArrayPair, temp.nodeNeg);
        int nodePosInArray = lookup(nodeNumInArrayPair, temp.nodePos);

        insertKoefisienTab(circuit_node_coefficient, nodeNegInArray,-1,
                nodePosInArray,1,temp.value);
    }

    free(isDone);
}

int findRow(double *row,double *ans,int* isDone,current_source_tab curr_list, resistor_tab res_list, voltage_source_tab volt_list,
            node_tab node_circuit,inductor_tab ind_list, capacitor_tab cap_list,  node_t node,struct table *nodeNumInArrayPair, double time_sample, int *udahAdaVoltage)
{
    // printf("node = %d\n",node.name);
    
    // for (i = 0; i <nodeNumInArrayPair->size; i++ ){
    //     printf("%f ",row[i]);
    // }
    // printf("\n");
    int i;
    if (isDone[lookup(nodeNumInArrayPair, node.name)]){
        return -1;
    }

    
    int total_node = nodeNumInArrayPair->size;
    

    voltage_source_t temp_vol;
    current_source_t temp_cur;
    resistor_t temp_res;
    capacitor_t temp_cap;

    isDone[lookup(nodeNumInArrayPair, node.name)] = 1;

    if (node.isGround){
        udahAdaVoltage[lookup(nodeNumInArrayPair, node.name)] = 1;
        return -1;        
    }
    
        // current source kcl (masuk = positif)
    for (i = 0; i < node.current_source_list.Neff;i++){
        temp_cur = curr_list.array[(node.current_source_list.array)[i]];
        if (temp_cur.nodePos == node.name){
            (*ans) -= temp_cur.value;
        }
        else{
            (*ans) += temp_cur.value;
        }
    }

    // resistance arus keluar positif
    for (i = 0; i < node.res_list.Neff; i++){
        temp_res = res_list.array[(node.res_list.array)[i]];
        row[lookup(nodeNumInArrayPair, node.name)] += 1 / (temp_res.value);
        if (temp_res.node1 != node.name){
            row[lookup(nodeNumInArrayPair, temp_res.node1)] -= 1 / (temp_res.value);
        }
        else{
            row[lookup(nodeNumInArrayPair, temp_res.node2)] -= 1 / (temp_res.value);
        }
    }

    // capacitor, node1 node positif
    for (i = 0; i < node.cap_list.Neff; i++){
        temp_cap = cap_list.array[(node.cap_list.array)[i]];
        row[lookup(nodeNumInArrayPair, node.name)] += temp_cap.value / (time_sample);
        if (temp_cap.node1 == node.name){
            (*ans) += temp_cap.value * temp_cap.last_volt/time_sample;
        }
        else{
            (*ans) -= temp_cap.value * temp_cap.last_volt/time_sample;
        }
        if (temp_res.node1 != node.name){
            row[lookup(nodeNumInArrayPair, node.name)] += temp_cap.value / (time_sample);
        }
        else{
            row[lookup(nodeNumInArrayPair, node.name)] -= temp_cap.value / (time_sample);
        }
    }   

    for (i = 0; i < node.voltage_source_list.Neff; i++){
        temp_vol = volt_list.array[node.voltage_source_list.array[i]];
        int nodeNegInArray = lookup(nodeNumInArrayPair, temp_vol.nodeNeg);
        int nodePosInArray = lookup(nodeNumInArrayPair, temp_vol.nodePos);
        if (node_circuit.array[nodeNegInArray].isGround || node_circuit.array[nodePosInArray].isGround){
            isDone[nodeNegInArray] = 1;
            isDone[nodePosInArray] = 1;
            udahAdaVoltage[nodeNegInArray] = 1;
            udahAdaVoltage[nodePosInArray] = 1;
            return -1;
        }

        // if (node.name != temp_vol.nodeNeg && isDone[nodeNegInArray] == 1){                     
        //     return -1;
        // }
        // else if (node.name != temp_vol.nodePos && isDone[nodePosInArray] == 1){             
        //     return -1;
        // }

    }

    for (i = 0; i < node.voltage_source_list.Neff; i++){

        temp_vol = volt_list.array[node.voltage_source_list.array[i]];
        int nodeNegInArray = lookup(nodeNumInArrayPair, temp_vol.nodeNeg);
        int nodePosInArray = lookup(nodeNumInArrayPair, temp_vol.nodePos);     
        
        // super node
        if (udahAdaVoltage[nodeNegInArray] || udahAdaVoltage[nodePosInArray]){
            return -1;
        }
        if (temp_vol.nodeNeg != node.name && !isDone[nodeNegInArray]){
            if (findRow(row, ans, isDone,curr_list, res_list, volt_list, node_circuit,
            ind_list, cap_list, node_circuit.array[nodeNegInArray],nodeNumInArrayPair,time_sample, udahAdaVoltage) == -1){
                return -1;
            }            
        }
        else if (node_circuit.array[nodePosInArray].name != node.name && !isDone[nodePosInArray]){
            if (findRow(row, ans, isDone,curr_list, res_list, volt_list, node_circuit,
            ind_list, cap_list, node_circuit.array[nodePosInArray],nodeNumInArrayPair,time_sample, udahAdaVoltage) == -1){
                return -1;
            }
        }
    }
    //-1 means ga bisa jadi supernode

    return 1;
}

void KCLAnalysisPerNode(koefisien_tab* circuit_node_coefficient,voltage_source_tab volt_list,current_source_tab curr_list, resistor_tab res_list, 
                        inductor_tab ind_list, capacitor_tab cap_list,  node_tab node_circuit,struct table *nodeNumInArrayPair, double time_sample)
{
    int total_node = circuit_node_coefficient->total_node;
    int i;
    int *isDone;
    isDone = (int*)calloc(total_node, sizeof(int));
    int *udahAdaVoltage;
    udahAdaVoltage = (int*)calloc(total_node, sizeof(int));
    
    double *row = (double *)calloc(total_node,sizeof(double));;
    double ans;
    printf("Total NEff = %d\n",circuit_node_coefficient->Neff);
    for (i = 0; i < total_node; i++){
        free(row);
        row = (double *)calloc(total_node,sizeof(double));
        ans = 0;
        if (!isDone[i]){
            // printf("i = %d\n",i)       ;
            if (findRow(row, &ans, isDone, curr_list, res_list, volt_list,node_circuit, ind_list, cap_list, node_circuit.array[i],nodeNumInArrayPair,time_sample, udahAdaVoltage) > 0){
                inserRowToKoefTab(circuit_node_coefficient, row, ans);
                // printf("Total NEff = %d\n",circuit_node_coefficient->Neff);
                // printf("debug");
            }
        }
    }
}

