#define METRIC_PARAMS 2

static void interactive_parse(char parameters[METRIC_PARAMS][2][64], char * ptr_unknown_choice, double * dia_pitch, double * met_module);
static void file_parse(char * input_file, char * ptr_unknown_choice, double * dia_pitch, double * met_module);
