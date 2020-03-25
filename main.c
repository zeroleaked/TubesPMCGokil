
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

#define DEBUG

int main(){
    int i , j , k;
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
        typeComponent = askInput();
    }

    #ifdef DEBUG
    for (i = 0; i < node_circuit.Neff;i++){
        printNode((node_circuit.array)[i] , resistor_list, capacitor_list
        ,inductor_list,voltage_source_list,current_source_list);
    }
    #endif
    
    
    return 0;
}
