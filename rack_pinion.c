#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "rack_pinion.h"


void rack_pinion(char * input_file)
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
      while (getchar()!='\n'); //clear stdin buffer
    }

  result=solve_rack_pinion(&unknown_choice);
  printf("Computed value for %c is %f\n",unknown_choice,result);  
}

float solve_rack_pinion(char * unknown)
{
  float nVal;
  float pVal;
  float sVal;
  float pi=(float)M_PI;

  switch (*unknown) {
  case 'N' : //number of teeth
    sVal=get_s();
    pVal=get_p();
    nVal=(sVal*1000)/(pi*pVal);
    return nVal;
    break;
  case 'P' : //pitch diameter of pinion
    sVal=get_s();
    nVal=get_n();
    pVal=(sVal*1000)/(pi*nVal);
    return pVal;
    break;
  case 'S' : //surface speed
    pVal=get_p();
    nVal=get_n();
    sVal=(pi*pVal*nVal)/1000;
    return sVal;
    break;
  default : //not recognized
    assert(*unknown!='N' || *unknown!='P' || *unknown!='S');
  }
}

float get_n(void)
{
  float N;
  
  printf("Provide a value for N (number of teeth): ");
  scanf("%f",&N);
  assert(N>7);
  return N;
}

float get_p(void)
{
  float P;
  
  printf("Provide a value for P (pitch diameter of pinion): ");
  scanf("%f",&P);
  assert(P>0);
  return P;
}

float get_s(void)
{
  float S;
  
  printf("Provide a value for S (surface speed of rack): ");
  scanf("%f",&S);
  assert(S>0);
  return S;
}
