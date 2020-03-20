#ifndef DEBUG_H
#define DEBUG_H

#include "configuration.h"
#include <stdio.h>

void printRes(resistor_t res){
    printf("Value = %f \n", res.value);
    printf("Node 1 = %f \n", res.node1);
    printf("Node 2 = %f \n", res.node2);
}

void printIn(inductor_t in){
    printf("Value = %f \n",        in.value);
    printf("Last Current = %f \n", in.last_curr);
    printf("Node 1 = %f \n",       in.node1);
    printf("Node 2 = %f \n",       in.node2);
}

void printCap(inductor_t cap){
    printf("Value = %f \n",        cap.value);
    printf("Last Current = %f \n", cap.last_curr);
    printf("Node 1 = %f \n",       cap.node1);
    printf("Node 2 = %f \n",       cap.node2);
}
#endif