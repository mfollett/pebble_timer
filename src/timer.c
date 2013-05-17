#include "pebble_os.h"
#include "pebble_app.h"
#include "time_handler.h"
#include "display.h"


#define MY_UUID { 0x5C, 0x1C, 0x2B, 0xE7, 0x80, 0x91, 0x4F, 0x95, 0xAB, 0xAA, 0x51, 0xE8, 0x0A, 0xA8, 0x9D, 0x4C }
PBL_APP_INFO(MY_UUID,
             "Timer", "Follett Co.",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

#define BUTTON_CLICK_TIME_SHIFT 30
#define INITIAL_TIME 5*60

bool listening_for_time_modification = true;

void handle_second_tick() {
    int time = current_time();

    if( ! listening_for_time_modification) {

        decrement_time();

        if(time == 0) {
            alert();
        }

        if( time < 5 && time > 0) {
            warning();
        }
    }

    update_display_with_time(time);
}

void start_timer() {
    listening_for_time_modification = false;
}

void handle_up() {
    if(listening_for_time_modification) {
        add_time(BUTTON_CLICK_TIME_SHIFT);
        update_display_with_time(current_time());
    }
}

void handle_down() {
    if(listening_for_time_modification) {
        subtract_time(BUTTON_CLICK_TIME_SHIFT);
        update_display_with_time(current_time());
    }
}

void click_config_provider(ClickConfig **config, Window *window) {
    config[BUTTON_ID_SELECT]->click.handler = (ClickHandler) start_timer;
    config[BUTTON_ID_UP]    ->click.handler = (ClickHandler) handle_up;
    config[BUTTON_ID_DOWN]  ->click.handler = (ClickHandler) handle_down;

    config[BUTTON_ID_UP]  ->click.repeat_interval_ms = 100;
    config[BUTTON_ID_DOWN]->click.repeat_interval_ms = 100;
}

void handle_init(AppContextRef ctx) {
  initialize_display();
  window_set_click_config_provider(get_window(), (ClickConfigProvider) click_config_provider);

  set_time(INITIAL_TIME);
  handle_second_tick(ctx, NULL);
}

void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .tick_info = {
        .tick_handler = &handle_second_tick,
        .tick_units   = SECOND_UNIT
    }
  };
  app_event_loop(params, &handlers);
}
