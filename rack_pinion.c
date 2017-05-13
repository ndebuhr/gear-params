#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "rack_pinion.h"


void rack_pinion(void)
{  
  int i;
  char parameters[NUM_PARAMS][2][64]={{"N","Number of Teeth"},{"P","Pitch Diameter of Pinion"},{"S","Surface Speed"}};
  bool valid_param=false;
  char unknown_choice;
  char toss_char;
  float result;
  
  printf("Index | Parameter Name\n");    
  for (i=0;i<NUM_PARAMS;i++)
    printf("%4s  | %s\n",parameters[i][0],parameters[i][1]);

  while (valid_param==false)
    {
      printf("\nParameter to solve for (enter index): ");
      scanf("%c",&unknown_choice);
      for (i=0;i<NUM_PARAMS;i++)
	{
	  if (unknown_choice==parameters[i][0][0])
	    valid_param=true;
	}
      if (valid_param==false)
	printf("Invalid index.  Please input an index from list (case sensitive).\n");
      scanf("%c",&toss_char); //toss \n character.  TODO clean this up
    }

  result=solve_rack_pinion(&unknown_choice);
  printf("%f\n",result);
  printf("%c\n",unknown_choice);
  
}

float solve_rack_pinion(char * unknown)
{
  switch (*unknown) {
  case 'N' : //number of teeth
    // (S*1000)/(pi*P)
    return 1;
    break;
  case 'P' : //pitch diameter of pinion
    // (S*1000)/(pi*N)
    return 2;
    break;
  case 'S' : //surface speed
    // (pi*P*N)/1000
    return 3;
    break;
  default : //not recognized
    assert(*unknown!='N' || *unknown!='P' || *unknown!='S');
  }
}
  
