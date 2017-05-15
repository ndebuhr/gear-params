/************************************************
 * Filename: gear_params.c
 * Neal DeBuhr
 *
 * Description: Central file for determining user
 * needs, and running corresponding functions
 *************************************************/ 

#include <stdio.h>
#include <stdbool.h>
#include "gear_params.h"
#include "get_teeth.h"
#include "rack_pinion.h"

int main(int argc, char * argv[])
{  
  char module_index;

  if (argc>1)
    {
      if (argv[1][0]=='-')
	module_index=module_choice(argv[1][1]);
      else
	module_index=module_choice('\0'); //command line module selection incorrectly formatted (ignore it)
    }
  else
    module_index=module_choice('\0'); //command line module selection not specified

  switch (module_index)
    {
    case 'S':
      get_teeth();
      break;
    case 'R':
      rack_pinion();
      break;
    default:
      break;
    }
  
  return 0;
}

char module_choice(char predet)
{
  int i;
  char user_choice;
  char char_dump;
  bool valid_input;
  char module_options[MODULES][MODULE_PARTS][MODULE_PART_SIZE]=
    {{"S","Spur Gear Train Design"},
     {"R","Rack and Pinion Design"}};

  if (predet=='\0')
    {
      // Print current modules available
      printf("Index | Module Name\n");
      for (i=0; i<MODULES; i++)
	printf("%4s  | %s\n",module_options[i][0],module_options[i][1]);
      printf("Module to run: ");
      scanf("%c",&user_choice);
      while (getchar()!='\n'); //clear stdin buffer
    }
  else
    {
      user_choice=predet;
    }
  
  do { // TODO clean this up without \n in buffer issue
    valid_input=module_exists(user_choice,module_options,MODULES);
    if (valid_input==false)
      {
	printf("Module index not recognized. Please input one from list.\n");
	printf("Module to run: ");
	scanf("%c",&user_choice);
	while (getchar()!='\n'); //clear stdin buffer
      }
  } while (valid_input==false);
  
  return user_choice;
}

bool module_exists(char user_choice, char module_opt_ptr[MODULES][MODULE_PARTS][MODULE_PART_SIZE], const int num_modules)
{
  int i;
  for (i=0; i<num_modules; i++)
    {
      if (user_choice == module_opt_ptr[i][0][0]) //limited to single digit module indexes
	return true;
    }
  return false;
}
