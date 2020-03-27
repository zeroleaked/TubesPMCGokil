#ifndef INPUT_H
#define INPUT_H

#include "stdio.h"
#include "../Configuration/configuration.h"

char askInput(){
    printf("Masukkan Komponen yang ingin diinput :");
    char temp;
    scanf(" %c" , &temp);
    return temp;
}
resistor_t askResistor(){
    resistor_t temp;
    printf("Masukkan nilai Resistor :");
    scanf("%lf", &(temp.value));
    printf("Masukkan node :");
    scanf("%d", &(temp.node1));
    printf("Masukkan node :");
    scanf("%d", &(temp.node2));
    return temp;  
}

capacitor_t askCapacitor(){
    capacitor_t temp;
    printf("Masukkan nilai Capacitor :");
    scanf("%lf", &(temp.value));
    printf("Masukkan node :");
    scanf("%d", &(temp.node1));
    printf("Masukkan node :");
    scanf("%d", &(temp.node2));
    printf("Masukkan nilai Tegangan saat t = t0 :");
    scanf("%lf", &(temp.last_volt));
    return temp;  
}

inductor_t askInductor(){
    inductor_t temp;
    printf("Masukkan nilai Induktor :");
    scanf("%lf", &(temp.value));
    printf("Masukkan node :");
    scanf("%d", &(temp.node1));
    printf("Masukkan node :");
    scanf("%d", &(temp.node2));
    printf("Masukkan nilai Arus saat t = t0 :");
    scanf("%lf", &(temp.last_curr));
    return temp;  
}

voltage_source_t askVoltageSource(){
    voltage_source_t temp;
    printf("Masukkan nilai Tegangan :");
    scanf("%lf", &(temp.value));
    printf("Masukkan nilai Node Positif :");
    scanf("%d", &(temp.nodePos));
    printf("Masukkan nilai Node Negatif :");
    scanf("%d", &(temp.nodeNeg));
    
    return temp;
}

current_source_t askCurrentSource(){
    current_source_t temp;
    printf("Masukkan nilai Arus :");
    scanf("%lf", &(temp.value));
    printf("Masukkan nilai Node Positif :");
    scanf("%d", &(temp.nodePos));
    printf("Masukkan nilai Node Negatif :");
    scanf("%d", &(temp.nodeNeg));

    return temp;
}

int askGround(){
    int node;
    printf("Masukkan node Ground :");
    scanf("%d", &node);
    return node;
}

void pushResToNodeArray(resistor_t res,int num_in_array ,node_tab *node_list){
    int i = 0;
    int found1 = 0;
    int found2 = 0;
    for (i = 0; i < node_list->Neff; i++){
        int tempName = (node_list->array)[i].name;
        if (tempName == res.node1){
            found1 = 1;
        }
        else if (tempName == res.node2){
            found2 = 1;
        }
    }

    if (found1 != 1){
        node_t tempNode = makeNode(res.node1);
        addNodeToTab(node_list,tempNode);
    }
    if (found2 != 1 && res.node1 != res.node2){
        node_t tempNode = makeNode(res.node2);
        addNodeToTab(node_list,tempNode);
    }

    for (i = 0; i < node_list->Neff; i++){
        int tempName = (node_list->array)[i].name;
        if (tempName == res.node1){
            addIntegerToTab(&((node_list->array)[i].res_list) , num_in_array);
        }
        else if (tempName == res.node2){
            addIntegerToTab(&((node_list->array)[i].res_list) , num_in_array);
        }
    }    
}

void pushindToNodeArray(inductor_t ind,int num_in_array ,node_tab *node_list){
    int i = 0;
    int found1 = 0;
    int found2 = 0;
    for (i = 0; i < node_list->Neff; i++){
        int tempName = (node_list->array)[i].name;
        if (tempName == ind.node1){
            found1 = 1;
        }
        else if (tempName == ind.node2){
            found2 = 1;
        }
    }

    if (found1 != 1){
        node_t tempNode = makeNode(ind.node1);
        addNodeToTab(node_list,tempNode);
    }
    if (found2 != 1 && ind.node1 != ind.node2){
        node_t tempNode = makeNode(ind.node2);
        addNodeToTab(node_list,tempNode);
    }

    for (i = 0; i < node_list->Neff; i++){
        int tempName = (node_list->array)[i].name;
        if (tempName == ind.node1){
            addIntegerToTab(&((node_list->array)[i].ind_list) , num_in_array);
        }
        else if (tempName == ind.node2){
            addIntegerToTab(&((node_list->array)[i].ind_list) , num_in_array);
        }
    }    
}

void pushCapToNodeArray(capacitor_t cap,int num_in_array ,node_tab *node_list){
    int i = 0;
    int found1 = 0;
    int found2 = 0;
    for (i = 0; i < node_list->Neff; i++){
        int tempName = (node_list->array)[i].name;
        if (tempName == cap.node1){
            found1 = 1;
        }
        else if (tempName == cap.node2){
            found2 = 1;
        }
    }

    if (found1 != 1){
        node_t tempNode = makeNode(cap.node1);
        addNodeToTab(node_list,tempNode);
    }
    if (found2 != 1 && cap.node1 != cap.node2){
        node_t tempNode = makeNode(cap.node2);
        addNodeToTab(node_list,tempNode);
    }

    for (i = 0; i < node_list->Neff; i++){
        int tempName = (node_list->array)[i].name;
        if (tempName == cap.node1){
            addIntegerToTab(&((node_list->array)[i].cap_list) , num_in_array);
        }
        else if (tempName == cap.node2){
            addIntegerToTab(&((node_list->array)[i].cap_list) , num_in_array);
        }
    }
}

void pushCurToNodeArray(current_source_t cur,int num_in_array ,node_tab *node_list){
    int i = 0;
    int found1 = 0;
    int found2 = 0;
    for (i = 0; i < node_list->Neff; i++){
        int tempName = (node_list->array)[i].name;
        if (tempName == cur.nodePos){
            found1 = 1;
        }
        else if (tempName == cur.nodeNeg){
            found2 = 1;
        }
    }

    if (found1 != 1){
        node_t tempNode = makeNode(cur.nodePos);
        addNodeToTab(node_list,tempNode);
    }
    if (found2 != 1 && cur.nodePos != cur.nodeNeg){
        node_t tempNode = makeNode(cur.nodeNeg);
        addNodeToTab(node_list,tempNode);
    }

    for (i = 0; i < node_list->Neff; i++){
        int tempName = (node_list->array)[i].name;
        if (tempName == cur.nodePos){
            addIntegerToTab(&((node_list->array)[i].current_source_list) , num_in_array);
        }
        else if (tempName == cur.nodeNeg){
            addIntegerToTab(&((node_list->array)[i].current_source_list) , num_in_array);
        }
    }
}

void pushVolToNodeArray(voltage_source_t vol,int num_in_array ,node_tab *node_list){
    int i = 0;
    int found1 = 0;
    int found2 = 0;
    for (i = 0; i < node_list->Neff; i++){
        int tempName = (node_list->array)[i].name;
        if (tempName == vol.nodePos){
            found1 = 1;
        }
        else if (tempName == vol.nodeNeg){
            found2 = 1;
        }
    }

    if (found1 != 1){
        node_t tempNode = makeNode(vol.nodePos);
        addNodeToTab(node_list,tempNode);
    }
    if (found2 != 1 && vol.nodePos != vol.nodeNeg){
        node_t tempNode = makeNode(vol.nodeNeg);
        addNodeToTab(node_list,tempNode);
    }

    for (i = 0; i < node_list->Neff; i++){
        int tempName = (node_list->array)[i].name;
        if (tempName == vol.nodePos){
            addIntegerToTab(&((node_list->array)[i].voltage_source_list) , num_in_array);
        }
        else if (tempName == vol.nodeNeg){
            addIntegerToTab(&((node_list->array)[i].voltage_source_list) , num_in_array);
        }
    }
}

void pushGroundToNodeArray(node_tab *node_list, int ground_node){
    int i;
    int found = 0;
    for (i = 0; i < node_list->Neff; i++){
        int tempName = (node_list->array)[i].name;
        if (tempName == ground_node){
            found = 1;
            (node_list->array)[i].isGround = 1;
        }
    }
    if (found == 0){
        node_t tempNode = makeNode(ground_node);
        tempNode.isGround = 1;
        addNodeToTab(node_list,tempNode);
    }
}
#endif