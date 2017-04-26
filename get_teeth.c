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

int main()
{  
  float speed_A, speed_B, teeth_A, teeth_B;
  float whole_speed_B1, whole_speed_B2;
  int whole_teeth_B1, whole_teeth_B2;
  
  printf("Enter the speed of the first gear:");
  scanf("%f",&speed_A);

  printf("Enter the speed of the second gear:");
  scanf("%f",&speed_B);

  printf("Enter the number of teeth of the first gear:");
  scanf("%f",&teeth_A);

  teeth_B=(speed_A*teeth_A)/speed_B;

  whole_teeth_B1=(int)teeth_B;
  whole_speed_B1=(speed_A*teeth_A)/(float)whole_teeth_B1;
  whole_teeth_B2=(int)teeth_B+1;
  whole_speed_B2=(speed_A*teeth_A)/(float)whole_teeth_B2;

  if ((float)whole_teeth_B1 != teeth_B)
    {
      printf("Closest possible speeds are:\n");
      printf("%.0f speed with a %d tooth gear\n",whole_speed_B1,whole_teeth_B1);
      printf("%.0f speed with a %d tooth gear\n",whole_speed_B2,whole_teeth_B2);
    }
  else
    {
      printf("%.0f speed attainable with a %.0f tooth gear\n",speed_B,teeth_B);
    }

  return 0;
}
