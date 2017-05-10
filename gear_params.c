/************************************************
 * Filename: gear_params.c
 * Neal DeBuhr
 *
 * Description: Central file for determining user
 * needs, and running corresponding functions
 *************************************************/ 

// TODO move preprocessor constants and function prototypes to header file
#include <stdio.h>
#include <stdbool.h>
#include "gear_params.h"

int main(void)
{  
  int module_index;
  module_index=module_choice();
  printf("%c\n",module_index);

  return 0;
}

char module_choice(void)
{
  int i;
  char user_choice;
  char char_dump;
  bool valid_input;
  char module_options[MODULES][MODULE_PARTS][MODULE_PART_SIZE]=
    {{"S","Spur Gear Train Design"},
     {"R","Rack and Pinion Design"}};

  // Print current modules available
  printf("Index | Module Name\n");
  for (i=0; i<MODULES; i++)
    printf("%4s  | %s\n",module_options[i][0],module_options[i][1]);
  
  do { // TODO clean this up without \n in buffer issue
    printf("Module to run: ");
    scanf("%c",&user_choice);
    valid_input=module_exists(user_choice,module_options,MODULES);
    if (valid_input==false)
      printf("Module number not recognized. Please input one from list.\n");
    scanf("%c",&char_dump); //dump \n from input buffer
  } while (valid_input==false);

  switch (user_choice)
    {
    case 'S':
      get_teeth();
      break;
    default:
      rack_pinion();
      break;
    }
  
  return 0;
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
