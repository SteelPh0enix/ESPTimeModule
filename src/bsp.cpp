#include "bsp.hpp"
#include <Arduino.h>

static bool board_led_state = false;

void toggle_board_led() {
  board_led_state = !board_led_state;
  digitalWrite(LED_BUILTIN, board_led_state);
}

void set_board_led_state(bool enabled) {
  board_led_state = enabled;
  digitalWrite(LED_BUILTIN, !board_led_state);
}

void enable_board_led() {
  set_board_led_state(true);
}

void disable_board_led() {
  set_board_led_state(false);
}
