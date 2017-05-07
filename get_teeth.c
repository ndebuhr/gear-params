/************************************************
 * Filename: get_teeth.c
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
#include "get_teeth.h"

void get_teeth(void)
{  
  float speed_A, speed_B, teeth_A;
  int output_teeth[2]={0,0};
  float output_speed[2]={0,0};
  int output_state;
  
  printf("Enter the speed of the first gear:");
  scanf("%f",&speed_A);
  assert(speed_A>0);
  
  printf("Enter the speed of the second gear:");
  scanf("%f",&speed_B);
  assert(speed_B>0);

  printf("Enter the number of teeth of the first gear:");
  scanf("%f",&teeth_A);
  assert(teeth_A>0);

  output_state=calc_output_teeth(speed_A,speed_B,teeth_A,output_teeth,output_speed);
  
  if (output_state==2) //single integer solution does not exist
    {
      printf("Closest possible speeds are:\n");
      printf("%.0f speed with a %d tooth output gear\n",output_speed[0],output_teeth[0]);
      printf("%.0f speed with a %d tooth output gear\n",output_speed[1],output_teeth[1]);
      check_num_min(teeth_A);
      check_num_min(output_teeth[0]);
      check_num_min(output_teeth[1]);
    }
  else //single integer solution does exist
    {
      printf("%.0f speed attainable with a %d tooth output gear\n",output_speed[0],output_teeth[0]);
      check_num_min(teeth_A);
      check_num_min(output_teeth[0]);
    }  
}

int calc_output_teeth(float speed_A, float speed_B, float teeth_A, int output_teeth[], float output_speed[])
{
  float teeth_B;
  
  teeth_B=(speed_A*teeth_A)/speed_B;
  
  output_teeth[0]=(int)teeth_B;
  output_speed[0]=(speed_A*teeth_A)/(float)output_teeth[0];
  output_teeth[1]=(int)teeth_B+1;
  output_speed[1]=(speed_A*teeth_A)/(float)output_teeth[1];

  if ((float)output_teeth[0] != teeth_B)
    return 2; //two closest integer values
  else
    return 1; //single integer value solves perfectly
}

void check_num_min(int num_teeth)
{
  if (num_teeth < 8)
    printf("Warning: %d gear teeth is below recommended minimum of 8.\n         Consider scaling all gear teeth numbers with a single multiplier.\n",num_teeth);
}
