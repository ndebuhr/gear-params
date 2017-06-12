#define NUM_PARAMS 3
#define INPUT_FILE_LINE 256

void rack_pinion(char * input_file);
float solve_rack_pinion(char * unknown, float nVal, float pVal, float sVal);
float get_n(void);
float get_p(void);
float get_s(void);
void rack_interactive_parse(char parameters[NUM_PARAMS][2][64],char * unknown_choice, float * nVal, float * pVal, float * sVal);
void rack_file_parse(char * input_file, char parameters[NUM_PARAMS][2][64],char * unknown_choice, float * nVal, float * pVal, float * sVal);


