/************************************************
 * Filename: spur_gears.c
 * Neal DeBuhr
 *
 * Description: Determines the gear teeth needed
 * to attain a user-specified output speed, given
 * an input speed and the number of teeth on the
 * first gear
 *************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "spur_gears.h"

void spur_gears(char * input_file)
{  
  struct spur {
    float speed;
    float teeth;
    int rSpeed;
    int rTeeth;
  };

  FILE * fp;
  char file_str[INPUT_FILE_LINE];
  char * var_parse;
  char * val_parse;
  
  struct spur driving;
  struct spur driven;

  char parameters[SPUR_PARAMS][2][64]={{"A","Driving Gear Speed"},{"B","Driving Gear Number of Teeth"},{"C","Driven Gear Speed"},{"D","Driven Gear Number of Teeth"}};
  bool valid_param=false;
  char unknown_choice;
  int i, j;

  if (strcmp(input_file,"Does Not Exist")==0)
    {
      printf("Index | Parameter Name\n");    
      for (i=0;i<SPUR_PARAMS;i++)
	printf("%4s  | %s\n",parameters[i][0],parameters[i][1]);
      unknown_choice=pick_unknown(parameters);

      if (unknown_choice != 'A')
	{
	  printf("Enter the speed of the driving gear:");
	  scanf("%f",&driving.speed);
	  assert(driving.speed>0);
	}
      
      if (unknown_choice != 'B')
	{
	  printf("Enter the number of teeth of the driving gear:");
	  scanf("%f",&driving.teeth);
	  assert(driving.teeth>0);
	}
      
      if (unknown_choice != 'C')
	{
	  printf("Enter the speed of the driven gear:");
	  scanf("%f",&driven.speed);
	  assert(driven.speed>0);
	}
      
      if (unknown_choice != 'D')
	{
	  printf("Enter the number of teeth of the driven gear:");
	  scanf("%f",&driven.teeth);
	  assert(driven.teeth>0);
	}
    }
  else
    {
      fp = fopen(input_file, "r"); //open file in read only
      while(fgets(file_str,INPUT_FILE_LINE,fp))
	{
	  printf("%s",file_str);
	  var_parse = (char *)calloc(strlen(file_str)+1,sizeof(char));
	  val_parse = (char *)calloc(strlen(file_str)+1,sizeof(char));
	  i=0;
	  while(file_str[i]!=' ')
	    var_parse[i]=file_str[i++];
	  var_parse[i]='\0';
	  i++;
	  if (file_str[i]=='?')
	    {
	      if (strcmp(var_parse,"driving.speed")==0)
		unknown_choice='A';
	      if (strcmp(var_parse,"driving.teeth")==0)
		unknown_choice='B';
	      if (strcmp(var_parse,"driven.speed")==0)
		unknown_choice='C';
	      if (strcmp(var_parse,"driven.teeth")==0)
		unknown_choice='C';
	      printf("Unknown choice is %c\n",unknown_choice);
	    }
	  else
	    {
	      j=0;
	      while(file_str[i]!='\0')
		val_parse[j++]=file_str[i++];
	      val_parse[j]='\0';
	      printf("%s\n",val_parse);
	      if (strcmp(var_parse,"driving.speed")==0)
		driving.speed=(float)val_parse;
	      if (strcmp(var_parse,"driving.teeth")==0)
		driving.teeth=(float)val_parse;
	      if (strcmp(var_parse,"driven.speed")==0)
		driven.speed=(float)val_parse;
	      if (strcmp(var_parse,"driven.teeth")==0)
		driven.teeth=(float)val_parse;
	    }
	  printf("%s\n",var_parse);
	  free(var_parse);
	}
      fclose(fp);
    }
      
  switch (unknown_choice) {
  case 'A':
    calc_speed(driving.teeth, driven.teeth, driven.speed, false);
    break;
  case 'B':
    calc_teeth(driving.speed, driven.speed, driven.teeth, false);
    break;
  case 'C':
    calc_speed(driving.teeth, driven.teeth, driving.speed, true);
    break;
  case 'D':
    calc_teeth(driving.speed, driven.speed, driving.teeth, true);
    break;
  }
}

void calc_speed(float inN, float outN, float known_speed, bool unknown_is_driven)
{
  float result_speed;
  
   if (unknown_is_driven)
    {
      result_speed=(inN/outN)*known_speed;
      printf("Driven gear speed is %f\n",result_speed);
    }
  else
    {
      result_speed=(outN/inN)*known_speed;
      printf("Driving gear speed is %f\n",result_speed);
    }
}

void calc_teeth(float in_speed, float out_speed, float known_teeth, bool unknown_is_driven)
{
  float f_speeds[2]={in_speed,out_speed};
  float f_teeth[2];
  
  int output_teeth[2]={0,0};
  float output_speed[2]={0,0};
  int output_state;
 
  if (unknown_is_driven)
    {
      f_teeth[0]=(float)known_teeth;
      f_teeth[1]=(f_speeds[0]*f_teeth[0])/f_speeds[1];
      output_teeth[0]=(int)f_teeth[1];
      output_speed[0]=(f_speeds[0]*f_teeth[0])/(float)output_teeth[0];
      output_teeth[1]=(int)f_teeth[1]+1;
      output_speed[1]=(f_speeds[0]*f_teeth[0])/(float)output_teeth[1];
      if ((float)output_teeth[0] != f_teeth[1])
	output_state=2; //two closest integer values
      else
	output_state=1; //single integer value solves perfectly
    }
  else //unknown is driving gear
    {
      f_teeth[1]=(float)known_teeth;
      f_teeth[0]=(f_speeds[1]*f_teeth[1])/f_speeds[0];
      output_teeth[0]=(int)f_teeth[0];
      output_speed[0]=(f_speeds[1]*f_teeth[1])/(float)output_teeth[0];
      output_teeth[1]=(int)f_teeth[0]+1;
      output_speed[1]=(f_speeds[1]*f_teeth[1])/(float)output_teeth[1];
      if ((float)output_teeth[0] != f_teeth[0])
	output_state=2; //two closest integer values
      else
	output_state=1; //single integer value solves perfectly
    }

  if (output_state==2) //single integer solution does not exist
    {
      printf("\nResults\nClosest possible speeds are:\n");
      printf("%.2f gear speed with a %d tooth gear\n",output_speed[0],output_teeth[0]);
      printf("%.2f gear speed with a %d tooth gear\n",output_speed[1],output_teeth[1]);
      check_num_min(output_teeth[0]);
      check_num_min(output_teeth[1]);
    }
  else //single integer solution does exist
    {
      printf("%.2f gear speed attainable with a %d tooth gear\n",output_speed[0],output_teeth[0]);
      check_num_min(output_teeth[0]);
    }
}

void check_num_min(int num_teeth)
{
  if (num_teeth < 8)
    printf("Warning: %d gear teeth is below recommended minimum of 8.\n         Consider scaling all gear teeth numbers with a single multiplier.\n",num_teeth);
}

char pick_unknown(char parameters[SPUR_PARAMS][2][64])
{
  int i;
  bool valid_param=false;
  char unknown_choice;
  
  while (valid_param==false)
    {
      printf("\nParameter to solve for (enter index): ");
      scanf("%c",&unknown_choice);
      for (i=0;i<SPUR_PARAMS;i++)
	{
	  if (unknown_choice==parameters[i][0][0])
	    valid_param=true;
	}
      if (valid_param==false)
	printf("Invalid index.  Please input an index from list (case sensitive).\n");
      while (getchar()!='\n'); //clear stdin buffer
    }

  return unknown_choice;
}
