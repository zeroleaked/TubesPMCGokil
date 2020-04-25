#include <stdio.h>
#include <stdlib.h>
#include "configuration.h"

int main() {
  component *com;
  int len = 0;
  char typ;
  double val;
  int n1;
  int n2;
  double t;

  typ = 'L';
  val = 5.5;
  n1 = 2;
  n2 = 3;
  t = 3;
initializeComponentArray(&com);
addComponent(&com, &len, typ, val, n1, n2, t);
printComponents(com, len, t);
printf("len = %d\n", len);
printf("%c, %f, %d, %d\n", com[0].type, com[0].value, com[0].node1, com[0].node2);
printf("%c, %f, %d, %d\n", com[1].type, com[1].value, com[1].node1, com[1].node2);
destroyComponentArray(&com);
}
