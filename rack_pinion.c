#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define NUM_PARAMS 3

void rack_pinion(void);

void rack_pinion(void)
{  
  int i;
  char parameters[NUM_PARAMS][2][64]={{"N","Number of Teeth"},{"P","Pitch Diameter of Pinion"},{"S","Surface Speed"}};
  
  for (i=0;i<NUM_PARAMS;i++)
    printf("%4s  | %s\n",parameters[i][0],parameters[i][1]);
  
}
