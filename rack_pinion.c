#include <stdio.h>
#include <stdbool.h>
#include "rack_pinion.h"

void rack_pinion(void)
{  
  int i;
  char parameters[NUM_PARAMS][2][64]={{"N","Number of Teeth"},{"P","Pitch Diameter of Pinion"},{"S","Surface Speed"}};
  bool valid_param=false;
  char unknown_choice;
  char toss_char;
  
  for (i=0;i<NUM_PARAMS;i++)
    printf("%4s  | %s\n",parameters[i][0],parameters[i][1]);

  while (valid_param==false)
    {
      printf("\nUnknown parameter (use single character index): ");
      scanf("%c",&unknown_choice);
      for (i=0;i<NUM_PARAMS;i++)
	{
	  if (unknown_choice==parameters[i][0][0])
	    valid_param=true;
	}
      if (valid_param==false)
	printf("Invalid chatacter index.  Please input one from list (case sensitive).\n");
      scanf("%c",&toss_char); //toss \n character.  TODO clean this up
    }

  printf("%c\n",unknown_choice);
  
}
