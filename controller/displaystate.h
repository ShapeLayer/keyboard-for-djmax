#ifndef __DISPLAYSTATE_H__
#define __DISPLAYSTATE_H__

#include <U8g2lib.h>
#include "config.h"

// Definitions
typedef struct {
  int sda;
  int scl;
} display_pin_t;

typedef struct {
  display_pin_t *pin;
  U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C *u8g2;
  bool is_cleared;
} display_state_t;

display_state_t new_display_state();

// Implementations
display_state_t new_display_state() {
  display_state_t state;
  display_pin_t pin;
  pin.sda = PIN_DISPLAY_SDA;
  pin.scl = PIN_DISPLAY_SCL;
  state.pin = &pin;
  state.u8g2 = nullptr;
  state.is_cleared = false;
  return state;
}


#endif  // __DISPLAYSTATE_H__
