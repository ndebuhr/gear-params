#define RACK_PARAMS 3

float solve_rack_pinion(char * unknown, float nVal, float pVal, float sVal);
float get_n(void);
float get_p(void);
float get_s(void);
void rack_interactive_parse(char parameters[RACK_PARAMS][2][64],char * unknown_choice, float * nVal, float * pVal, float * sVal);
void rack_file_parse(char * input_file, char parameters[RACK_PARAMS][2][64],char * unknown_choice, float * nVal, float * pVal, float * sVal);


