#define MODULES 3
#define MODULE_PARTS 2
#define MODULE_PART_SIZE 64

char choose_mod(char predet);
bool module_exists(char user_choice, char module_opt_ptr[MODULES][MODULE_PARTS][MODULE_PART_SIZE], const int num_modules);
