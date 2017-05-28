#define SPUR_PARAMS 4
void spur_gears(char * input_file);
void calc_speed(float inN, float outN, float known_speed, bool unknown_is_driven);
void calc_teeth(float in_speed, float out_speed, float known_teeth, bool unknown_is_driven);
void check_num_min(int num_teeth);
