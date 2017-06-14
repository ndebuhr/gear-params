#include "common.h"
#include "metric_US.h"

void metric_US(char * input_file)
{  
  int i;
  char parameters[METRIC_PARAMS][2][64]={{"M","Module (Metric)"},{"P","Diametral Pitch (US)"}};
  char unknown_choice='\0';
  char toss_char;
  double dia_pitch, met_module;

  if (strcmp(input_file,"Does Not Exist")==0)
    interactive_parse(parameters,&unknown_choice,&dia_pitch,&met_module);
  else
    file_parse(input_file,&unknown_choice,&dia_pitch,&met_module);
  
  switch (unknown_choice){
  case 'M' :
    met_module=25.4/dia_pitch;
    assert(dia_pitch>0);
    printf("Module is %f\n",met_module);
    break;
  case 'P' :
    dia_pitch=25.4/met_module;
    assert(met_module>0);
    printf("Diametral pitch is %f\n",dia_pitch);
    break;
  }

}

static void interactive_parse(char parameters[METRIC_PARAMS][2][64], char * ptr_unknown_choice, double * dia_pitch, double * met_module)
{
  int i;
  bool valid_param=false;

  printf("Index | Parameter Name\n");    
  for (i=0;i<METRIC_PARAMS;i++)
    printf("%4s  | %s\n",parameters[i][0],parameters[i][1]);

  while (valid_param==false)
    {
      printf("\nParameter to solve for (enter index): ");
      scanf("%c",ptr_unknown_choice);
      for (i=0;i<METRIC_PARAMS;i++)
	{
	  if (*ptr_unknown_choice==parameters[i][0][0])
	    valid_param=true;
	}
      if (valid_param==false)
	printf("Invalid index.  Please input an index from list (case sensitive).\n");
      while (getchar()!='\n'); //clear stdin buffer
    }

  switch (*ptr_unknown_choice){
  case 'M' :
    printf("Diametral pitch: ");
    scanf("%lf",dia_pitch);
    assert(dia_pitch>0);
    break;
  case 'P' :
    printf("Module: ");
    scanf("%lf",met_module);
    assert(met_module>0);
    break;
  }

}


static void file_parse(char * input_file, char * unknown_choice, double * dia_pitch, double * met_module)
{
  FILE * fp;
  char file_str[INPUT_FILE_LINE];
  char * var_parse;
  char * val_parse;
  int i, j;
  
  fp = fopen(input_file, "r"); //open file in read only
  *dia_pitch=0;
  *met_module=0;
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
	  if (strcmp(var_parse,"dia_pitch")==0)
	    *unknown_choice='P';
	  if (strcmp(var_parse,"met_module")==0)
	    *unknown_choice='M';
	}
      else
	{
	  j=0;
	  while(file_str[i]!='\0')
	    val_parse[j++]=file_str[i++];
	  val_parse[j]='\0';
	  if (strcmp(var_parse,"dia_pitch")==0)
	    {
	      printf("Dia_pitch set to %f\n",atof(val_parse));
	      assert(atof(val_parse)>0);
	      *dia_pitch=atof(val_parse);
	    }
	  if (strcmp(var_parse,"met_module")==0)
	    {
	      printf("Met_module set to %f\n",atof(val_parse));
	      assert(atof(val_parse)>0);
	      *met_module=atof(val_parse);
	    }
	}
      free(var_parse);
      free(val_parse);
    }
  fclose(fp);
  assert((*dia_pitch==0)^(*met_module==0)); //XOR check on value assignments to exactly 1 unknown
  assert(*unknown_choice!='\0'); //Ensure unknown variable was specified
}
