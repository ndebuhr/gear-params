#include <stdbool.h>

#define MODULES 4
#define MODULE_PARTS 2
#define MODULE_PART_SIZE 256

char module_choice(char predet);
bool module_exists(char user_choice, char module_opt_ptr[MODULES][MODULE_PARTS][MODULE_PART_SIZE], const int num_modules);
