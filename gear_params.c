#include "common.h"
#include "gear_params.h"

int main(int argc, char * argv[])
{  
  char mod_choice;
  int i;
  int j;
  bool mod_specified=false;
  bool input_file_exists=false;
  struct gear_mod {
    char index; //character index for module
    void (*func)(char *); //associated module function
  };
  struct gear_mod mod_spur_gear, mod_rack_pinion,
    mod_metric_US;
  mod_spur_gear.index='S';
  mod_spur_gear.func=&spur_gears;
  mod_rack_pinion.index='R';
  mod_rack_pinion.func=&rack_pinion;
  mod_metric_US.index='U';
  mod_metric_US.func=&metric_US;
  struct gear_mod modules[MODULES]={mod_spur_gear, mod_rack_pinion, mod_metric_US};
  char * input_file;
  
  if (argc>1)
    {
      for (i=1; i<argc; i++)
	{
	  if ( strcmp(argv[i],"-m") == 0)
	    {
	      mod_choice = ((i+1<argc) ? choose_mod(argv[i+1][0]) : choose_mod('\0')); //if flag, then ignore, if option, then read
	      mod_specified = true;
	    }
	  if ( strcmp(argv[i],"-i") == 0)
	    {
	      if (i+1<argc)
		{
		  input_file = (char *)calloc(strlen(argv[i+1])+1,sizeof(char));
		  j=0;
		  while (argv[i+1][j]!='\0') {
		    input_file[j]=argv[i+1][j];
		    j++;
		  }
		  input_file[j]='\0';
		  printf("Input file: %s\n",input_file);
		  input_file_exists=true;
		}
	    }
	}
      if (mod_specified==false)
	mod_choice=choose_mod('\0'); //command line module specification incorrectly formatted (ignore it)
    }
  else
    mod_choice=choose_mod('\0'); //command line module not specified

  if (input_file_exists==false)
    {
      input_file = (char *)calloc(strlen("Does Not Exist")+1,sizeof(char));
      strcpy(input_file, "Does Not Exist");
    }
  for (i=0; i<MODULES; i++)
    {
      if (mod_choice==modules[i].index) //if specified module matches the ith module index
	(*modules[i].func)(input_file); //run corresponding module function
    }

  free(input_file);
  return 0;
}

char choose_mod(char predet)
{
  int i;
  char user_choice;
  char char_dump;
  bool valid_input;
  char module_options[MODULES][MODULE_PARTS][MODULE_PART_SIZE]=
    {{"S","Spur Gear Train Design"},
     {"R","Rack and Pinion Design"},
     {"U","Unit Conversion Module vs. Diametral Pitch"}};

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
  
  do {
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
