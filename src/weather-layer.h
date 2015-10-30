#pragma once

#include <pebble.h>

#define WEATHER_EXPIRY_SECS 60 * 60
#define WEATHER_UPDATE_SECS 15 * 60

void weather_update(struct tm *tick_time);
void weather_window_load(Window *window);
void weather_window_unload(Window *window);
void weather_init();
void weather_deinit();
