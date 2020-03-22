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

int main(){
    char typeComponent = askInput();
    initiateNodeTab(&node_circuit);
    initiateResTab(&resistor_list);
    initiateInTab(&inductor_list)
    while (typeComponent != 'z'){
        if (typeComponent == 'r'){
            temp_resistor = askResistor();
            addResToTab(&resistor_list , temp_resistor);
            pushResToNodeArray(temp_resistor,(resistor_list.Neff) - 1,&node_circuit);
        }
        else if(typeComponent == 'i'){
            temp_inductor = askInductor();
            addInToTab(&inductor_list, temp_inductor);
            pushindToNodeArray(temp_inductor,(inductor_list.Neff) -1,&node_circuit);
        }
        typeComponent = askInput();
    }
    int i = 0;
    for (; i < node_circuit.Neff;i++){
        printNode((node_circuit.array)[i] , resistor_list, capacitor_list
        ,inductor_list,voltage_source_list,current_source_list);
    }

    
    
    
    return 0;
}