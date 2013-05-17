// gives me timer_t
#include "sys/types.h"

void add_time(timer_t amount);
void subtract_time(timer_t amount);

timer_t current_time();
void set_time(timer_t t);
void decrement_time();
