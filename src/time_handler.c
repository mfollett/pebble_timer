#include "time_handler.h"

timer_t time_left;

void add_time(timer_t amount) {
    if(time_left < 99*60) {
        time_left += amount;
    }
}

void subtract_time(timer_t amount) {
    if(time_left > amount) {
        time_left -= amount;
    } else {
        time_left = 0;
    }
}

void decrement_time() {
    if(time_left != 0) {
        time_left--;
    }
}

timer_t current_time() {
    return time_left;
}

void set_time(timer_t t) {
    time_left = t;
}
