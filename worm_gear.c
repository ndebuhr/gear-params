#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "worm_gear.h"


void worm_gear(char * input_file)
{  
  int i;
  char parameters[WORM_PARAMS][2][64]={{"1","Wormgear Param 1"},{"2","Wormgear Param 2"},{"3","Wormgear Param 3"}};
  bool valid_param=false;
  char unknown_choice;
  float result;
  
  printf("Index | Parameter Name\n");    
  for (i=0;i<WORM_PARAMS;i++)
    printf("%4s  | %s\n",parameters[i][0],parameters[i][1]);

  while (valid_param==false)
    {
      printf("\nParameter to solve for (enter index): ");
      scanf("%c",&unknown_choice);
      for (i=0;i<WORM_PARAMS;i++)
	{
	  if (unknown_choice==parameters[i][0][0])
	    valid_param=true;
	}
      if (valid_param==false)
	printf("Invalid index.  Please input an index from list (case sensitive).\n");
      while (getchar()!='\n'); //clear stdin buffer
    }

  result=1.0;
  printf("Computed value for %c is %f\n",unknown_choice,result);  
}
