#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "metric_US.h"


void metric_US(char * input_file)
{  
  int i;
  char parameters[UNIT_PARAMS][2][64]={{"M","Module (Metric)"},{"P","Diametral Pitch (US)"}};
  char unknown_choice;
  char toss_char;
  double dia_pitch, met_module;

  if (strcmp(input_file,"Does Not Exist")==0)
    metric_interactive_parse(parameters,&unknown_choice,&dia_pitch,&met_module);
  else
    metric_file_parse();
  
  switch (unknown_choice){
  case 'M' :
    met_module=25.4/dia_pitch;
    assert(dia_pitch>0);
    printf("Module is %f\n",met_module);
    break;
  case 'P' :
    dia_pitch=25.4/met_module;
    assert(met_module>0);
    printf("Diametral pitch is %f\n",dia_pitch);
    break;
  }

}

void metric_interactive_parse(char parameters[UNIT_PARAMS][2][64], char * ptr_unknown_choice, double * dia_pitch, double * met_module)
{
  int i;
  bool valid_param=false;

  printf("Index | Parameter Name\n");    
  for (i=0;i<UNIT_PARAMS;i++)
    printf("%4s  | %s\n",parameters[i][0],parameters[i][1]);

  while (valid_param==false)
    {
      printf("\nParameter to solve for (enter index): ");
      scanf("%c",ptr_unknown_choice);
      for (i=0;i<UNIT_PARAMS;i++)
	{
	  if (*ptr_unknown_choice==parameters[i][0][0])
	    valid_param=true;
	}
      if (valid_param==false)
	printf("Invalid index.  Please input an index from list (case sensitive).\n");
      while (getchar()!='\n'); //clear stdin buffer
    }

  switch (*ptr_unknown_choice){
  case 'M' :
    printf("Diametral pitch: ");
    scanf("%lf",dia_pitch);
    break;
  case 'P' :
    printf("Module: ");
    scanf("%lf",met_module);
    break;
  }

}


void metric_file_parse(void)
{
  printf("TODO\n");
}
