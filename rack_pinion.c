#include "common.h"
#include "rack_pinion.h"

void rack_pinion(char * input_file)
{  
  char parameters[RACK_PARAMS][2][64]={{"N","Number of Teeth"},{"P","Pitch Diameter of Pinion"},{"S","Surface Speed"}};
  char unknown_choice;
  float result;

  float nVal;
  float pVal;
  float sVal;
  
  if (strcmp(input_file,"Does Not Exist")==0)
    interactive_parse(parameters,&unknown_choice,&nVal,&pVal,&sVal);
  else
    file_parse(input_file,parameters,&unknown_choice,&nVal,&pVal,&sVal);

    
  result=solve_rack_pinion(&unknown_choice,nVal,pVal,sVal);
  printf("Computed value for %c is %f\n",unknown_choice,result);  
}

float solve_rack_pinion(char * unknown, float nVal, float pVal, float sVal)
{
  float pi=(float)M_PI;

  switch (*unknown) {
  case 'N' : //number of teeth
    nVal=(sVal*1000)/(pi*pVal);
    return nVal;
    break;
  case 'P' : //pitch diameter of pinion
    pVal=(sVal*1000)/(pi*nVal);
    return pVal;
    break;
  case 'S' : //surface speed
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

static void interactive_parse(char parameters[RACK_PARAMS][2][64],char * unknown_choice, float * nVal, float * pVal, float * sVal)
{
  int i;
  bool valid_param=false;
  char toss_char;
  
  printf("Index | Parameter Name\n");    
  for (i=0;i<RACK_PARAMS;i++)
    printf("%4s  | %s\n",parameters[i][0],parameters[i][1]);

  while (valid_param==false)
    {
      printf("\nParameter to solve for (enter index): ");
      scanf("%c",unknown_choice);
      for (i=0;i<RACK_PARAMS;i++)
	{
	  if (*unknown_choice==parameters[i][0][0])
	    valid_param=true;
	}
      if (valid_param==false)
	printf("Invalid index.  Please input an index from list (case sensitive).\n");
      while (getchar()!='\n'); //clear stdin buffer
    }
  
  switch (*unknown_choice) {
  case 'N' : //number of teeth
    *sVal=get_s();
    *pVal=get_p();
    break;
  case 'P' : //pitch diameter of pinion
    *sVal=get_s();
    *nVal=get_n();
    break;
  case 'S' : //surface speed
    *pVal=get_p();
    *nVal=get_n();
    break;
  }
}

static void file_parse(char * input_file, char parameters[RACK_PARAMS][2][64],char * unknown_choice, float * nVal, float * pVal, float * sVal)
{
  FILE * fp;
  char file_str[INPUT_FILE_LINE];
  char * var_parse;
  char * val_parse;
  int i, j;
  
  fp = fopen(input_file, "r"); //open file in read only
  while(fgets(file_str,INPUT_FILE_LINE,fp))
    {
      var_parse = (char *)calloc(strlen(file_str)+1,sizeof(char));
      val_parse = (char *)calloc(strlen(file_str)+1,sizeof(char));
      i=0;
      while(file_str[i]!=' ')
	var_parse[i]=file_str[i++];
      var_parse[i]='\0';
      i++;
      if (file_str[i]=='?')
	{
	  if (strcmp(var_parse,"nVal")==0)
	    *unknown_choice='N';
	  if (strcmp(var_parse,"pVal")==0)
	    *unknown_choice='P';
	  if (strcmp(var_parse,"sVal")==0)
	    *unknown_choice='S';
	}
      else
	{
	  j=0;
	  while(file_str[i]!='\0')
	    val_parse[j++]=file_str[i++];
	  val_parse[j]='\0';
	  if (strcmp(var_parse,"nVal")==0)
	    {
	      printf("nVal set to %f\n",atof(val_parse));
	      *nVal=atof(val_parse);
	    }
	  if (strcmp(var_parse,"pVal")==0)
	    {
	      printf("pVal set to %f\n",atof(val_parse));
	      *pVal=atof(val_parse);
	    }
	  if (strcmp(var_parse,"sVal")==0)
	    {
	      printf("sVal set to %f\n",atof(val_parse));  
	      *sVal=atof(val_parse);
	    }
	}
      free(var_parse);
      free(val_parse);
    }
  fclose(fp);
}  
