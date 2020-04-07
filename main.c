
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "Configuration/configuration.h"
#include "Configuration/debug.h"
#include "Configuration/procedure.h"
#include "Configuration/variable.h"
#include "Input/input.h"
#include "Matrices/matrices.h"
#include "Model/model.h"

// #define DEBUG

int main(){
    int i , j , k;
    out = fopen("out.txt","w");
    initiateNodeTab(&node_circuit);

    // initiate tab for component
    initiateResTab(&resistor_list);
    initiateInTab(&inductor_list);

    // input component
    char typeComponent = askInput();
    while (typeComponent != 'z'){
        if (typeComponent == 'r'){
            temp_resistor = askResistor();
            addResToTab(&resistor_list , temp_resistor);
            pushResToNodeArray(temp_resistor,(resistor_list.Neff) -1,&node_circuit);
        }
        else if(typeComponent == 'i'){
            temp_inductor = askInductor();
            addInToTab(&inductor_list, temp_inductor);
            pushindToNodeArray(temp_inductor,(inductor_list.Neff) -1,&node_circuit);
        }
        else if (typeComponent == 'c'){
            temp_capacitor = askCapacitor();
            addCapToTab(&capacitor_list, temp_capacitor);
            pushCapToNodeArray(temp_capacitor,(capacitor_list.Neff) -1,&node_circuit);
        }
        else if (typeComponent == 'A'){
            temp_current_source = askCurrentSource();
            addCurToTab(&current_source_list, temp_current_source);
            pushCurToNodeArray(temp_current_source,(current_source_list.Neff) -1,&node_circuit);
        }
        else if(typeComponent == 'V'){
            temp_voltage_source = askVoltageSource();
            addVolToTab(&voltage_source_list, temp_voltage_source);
            pushVolToNodeArray(temp_voltage_source,(voltage_source_list.Neff) -1,&node_circuit);
        }
        else if (typeComponent == 'G'){
            int temp_node = askGround();
            pushGroundToNodeArray(&node_circuit , temp_node);
        }
        typeComponent = askInput();
    }
    //making hash map for circuit
    nodeNumInArrayPair = createTable(node_circuit.Neff);

    for (i = 0; i < node_circuit.Neff; i++){
        insert(nodeNumInArrayPair, node_circuit.array[i].name, i);
    }
    #ifdef DEBUG
    for (i = 0; i < node_circuit.Neff; i++){
        printf("%d berada di urutan %d \n",node_circuit.array[i].name,lookup(nodeNumInArrayPair , node_circuit.array[i].name));
    }
    #endif



    printf("Masukkan Nilai Waktu Awal Simulasi :");
    scanf("%lf",&time_start);
    printf("Masukkan Nilai Waktu Akhir dari Simulasi \n");
    scanf("%lf",&time_end);
    
    //for saving coefficient
    circuit_node_coefficient = makeKoefisienTab(node_circuit.Neff);

    // voltage_in_node_now = (double**)calloc(node_circuit.Neff, sizeof(double*));

    // for (time_now = time_start; time_now <= time_end; time_start+=SMALLEST_TIME_SAMPLING){
    //     solveCircuit();
    //     outputToFile();
    // }

    #ifdef DEBUG
    for (i = 0; i < node_circuit.Neff;i++){
        printNode((node_circuit.array)[i] , resistor_list, capacitor_list
        ,inductor_list,voltage_source_list,current_source_list);
    }
    #endif

    // solve circuit
    // Circuit Analysis
    time_sample = SMALLEST_TIME_SAMPLING;
    makeMatricesVoltage(&circuit_node_coefficient,voltage_source_list,node_circuit,nodeNumInArrayPair);
    
    KCLAnalysisPerNode(&circuit_node_coefficient,voltage_source_list, current_source_list,
    resistor_list, inductor_list, capacitor_list, node_circuit, nodeNumInArrayPair,time_sample);
    
        
    #ifdef DEBUG
    for (i = 0; i < node_circuit.Neff; i++){
        printf("%d ",node_circuit.array[i].name);
    }
    printf("\n");
    #endif

    #ifdef DEBUG
    printMatrix(circuit_node_coefficient.array_koef, node_circuit.Neff);
    printArray(circuit_node_coefficient.ans, node_circuit.Neff);
    #endif

    double det_value = findDeterminant(circuit_node_coefficient.array_koef, node_circuit.Neff);
    
    
    voltage_in_node_now = matrixMultSquareTimesOneColumn(node_circuit.Neff, adjoint(circuit_node_coefficient.array_koef, node_circuit.Neff), 
    circuit_node_coefficient.ans);
    scalarMatrixMultiplication(1/det_value, node_circuit.Neff,voltage_in_node_now);

    for (i = 0; i < node_circuit.Neff; i++){
        printf("V di node %d adalah %f\n",node_circuit.array[i].name,voltage_in_node_now[i]);
    }

    // output to file


    
    
    
    return 0;
}
 