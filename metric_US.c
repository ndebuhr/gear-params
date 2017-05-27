#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "metric_US.h"


void metric_US(void)
{  
  int i;
  char parameters[UNIT_PARAMS][2][64]={{"M","Module (Metric)"},{"P","Diametral Pitch (US)"}};
  bool valid_param=false;
  char unknown_choice;
  char toss_char;
  double dia_pitch, met_module;
  
  printf("Index | Parameter Name\n");    
  for (i=0;i<UNIT_PARAMS;i++)
    printf("%4s  | %s\n",parameters[i][0],parameters[i][1]);

  while (valid_param==false)
    {
      printf("\nParameter to solve for (enter index): ");
      scanf("%c",&unknown_choice);
      for (i=0;i<UNIT_PARAMS;i++)
	{
	  if (unknown_choice==parameters[i][0][0])
	    valid_param=true;
	}
      if (valid_param==false)
	printf("Invalid index.  Please input an index from list (case sensitive).\n");
      while (getchar()!='\n'); //clear stdin buffer
    }

  switch (unknown_choice){
  case 'M' :
    printf("Diametral pitch: ");
    scanf("%lf",&dia_pitch);
    met_module=25.4/dia_pitch;
    printf("Module is %f\n",met_module);
    break;
  case 'P' :
    printf("Module: ");
    scanf("%lf",&met_module);
    dia_pitch=25.4/met_module;
    printf("Diametral pitch is %f\n",dia_pitch);
    break;
  }

}
