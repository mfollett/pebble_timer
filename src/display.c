#include "display.h"

#define TOGGLE(x) x = !x

bool flash_background = true;
bool light_enabled    = false;

Window window;

TextLayer timer;

void update_display_with_time(int time_left) {
    static char time_text[] = "00:00:00";
    PblTm pebble_time_left = {
        .tm_sec = time_left%60,
        .tm_min = time_left/60
    };

    string_format_time(time_text, sizeof(time_text), "%M:%S", &pebble_time_left);

    text_layer_set_text(&timer,time_text);
}

void alert() {
    vibes_short_pulse();
    TOGGLE(light_enabled);
    light_enable(light_enabled);
}

void warning() {
    int foreground = (flash_background ? GColorBlack : GColorWhite);
    int background = (flash_background ? GColorWhite : GColorBlack);
    text_layer_set_text_color(&timer, foreground);
    window_set_background_color(&window, background);
    TOGGLE(flash_background);
}

Window* get_window() {
    return &window;
}

void initialize_display() {
  window_init(&window, "Timer");
  window_stack_push(&window, true);
  window_set_background_color(&window, GColorBlack);

  text_layer_init(&timer, GRect(29, 54, 110, 50));
  text_layer_set_text_color(&timer, GColorWhite);
  text_layer_set_background_color(&timer, GColorClear);
  text_layer_set_font(&timer, fonts_get_system_font(FONT_KEY_GOTHAM_30_BLACK));

  layer_add_child(&window.layer, &timer.layer);

  text_layer_set_text(&timer, "Starting...");

}
