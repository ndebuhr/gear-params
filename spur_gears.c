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
#include <stdbool.h>
#include <assert.h>
#include "spur_gears.h"

void spur_gears(void)
{  
  struct spur {
    float speed;
    float teeth;
    int rSpeed;
    int rTeeth;
  };

  struct spur driving;
  struct spur driven;
  
  int output_teeth[2]={0,0};
  float output_speed[2]={0,0};
  int output_state;
  
  printf("Enter the speed of the driving gear:");
  scanf("%f",&driving.speed);
  assert(driving.speed>0);
  
  printf("Enter the speed of the driven gear:");
  scanf("%f",&driven.speed);
  assert(driven.speed>0);

  printf("Enter the number of teeth of the driving gear:");
  scanf("%f",&driving.teeth);
  assert(driving.teeth>0);

  output_state=calc_output_teeth(driving.speed,driven.speed,driving.teeth,output_teeth,output_speed);
  
  if (output_state==2) //single integer solution does not exist
    {
      printf("Closest possible speeds are:\n");
      printf("%.0f driven gear speed with a %d tooth gear\n",output_speed[0],output_teeth[0]);
      printf("%.0f driven gear speed with a %d tooth gear\n",output_speed[1],output_teeth[1]);
      check_num_min(driving.teeth);
      check_num_min(output_teeth[0]);
      check_num_min(output_teeth[1]);
    }
  else //single integer solution does exist
    {
      printf("%.0f driven gear speed attainable with a %d tooth gear\n",output_speed[0],output_teeth[0]);
      check_num_min(driving.teeth);
      check_num_min(output_teeth[0]);
    }  
}

int calc_output_teeth(float speed_A, float speed_B, float teeth_A, int output_teeth[], float output_speed[])
{
  float f_speeds[2]={speed_A,speed_B};
  float f_teeth[2]={teeth_A};
  
  f_teeth[1]=(f_speeds[0]*f_teeth[0])/f_speeds[1];
  
  output_teeth[0]=(int)f_teeth[1];
  output_speed[0]=(f_speeds[0]*f_teeth[0])/(float)output_teeth[0];
  output_teeth[1]=(int)f_teeth[1]+1;
  output_speed[1]=(f_speeds[0]*f_teeth[0])/(float)output_teeth[1];

  if ((float)output_teeth[0] != f_teeth[1])
    return 2; //two closest integer values
  else
    return 1; //single integer value solves perfectly
}

void check_num_min(int num_teeth)
{
  if (num_teeth < 8)
    printf("Warning: %d gear teeth is below recommended minimum of 8.\n         Consider scaling all gear teeth numbers with a single multiplier.\n",num_teeth);
}
