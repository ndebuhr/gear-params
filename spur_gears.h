#define SPUR_PARAMS 4

void calc_speed(float inN, float outN, float known_speed, bool unknown_is_driven);
void calc_teeth(float in_speed, float out_speed, float known_teeth, bool unknown_is_driven);
void check_num_min(int num_teeth);
char pick_unknown(char parameters[SPUR_PARAMS][2][64]);
static void interactive_parse(char parameters[SPUR_PARAMS][2][64], char * ptr_unknown_choice, float * driving_speed, float * driving_teeth, float * driven_speed, float * driven_teeth);
static void file_parse(char * input_file, char * ptr_unknown_choice, float * driving_speed, float * driving_teeth, float * driven_speed, float * driven_teeth);

