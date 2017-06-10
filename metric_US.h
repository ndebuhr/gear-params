#define UNIT_PARAMS 2

void metric_US(char * input_file);
void metric_interactive_parse(char parameters[UNIT_PARAMS][2][64], char * ptr_unknown_choice, double * dia_pitch, double * met_module);
void metric_file_parse(void);
