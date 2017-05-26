/************************************************
 * Gear design system
 * Neal DeBuhr
 *
 * Description: Central file for determining user
 * needs, and running corresponding modules
 *************************************************/ 

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "gear_params.h"
#include "get_teeth.h"
#include "rack_pinion.h"
#include "worm_gear.h"

int main(int argc, char * argv[])
{  
  char module_index;
  int i;
  bool mod_specified=false;
  
  if (argc>1)
    {
      for (i=1; i<argc; i++)
	{
	  if ( strcmp(argv[i],"-m") == 0)
	    {
	      module_index = ((i+1<argc) ? module_choice(argv[i+1][0]) : module_choice('\0'));
	      mod_specified = true;
	    }
	}
      if (mod_specified==false)
	module_index=module_choice('\0'); //command line module specification incorrectly formatted (ignore it)
    }
  else
    module_index=module_choice('\0'); //command line module not specified

  switch (module_index)
    {
    case 'S':
      get_teeth();
      break;
    case 'R':
      rack_pinion();
      break;
    case 'W':
      worm_gear();
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
     {"R","Rack and Pinion Design"},
     {"W","Worm Gear Design"}};

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
