#ifndef __KNOBSTATE_H__
#define __KNOBSTATE_H__

#include "config.h"

// Definitions
enum knob_state_e {
  KNOB_IDLE = 0,
  KNOB_ROTATE_CW = -1,
  KNOB_ROTATE_CCW = 1
};

typedef struct {
  int clk;
  int dt;
  int sw;
} knob_pin_t;

typedef struct {
  knob_pin_t *pin;
  int last_clk;
  knob_state_e state;
  unsigned long last_rotation_time;  // For debouncing
} knob_state_t;

knob_state_t new_knob_state();
void init_knob_pins(knob_state_t *);

// Implementations
knob_state_t new_knob_state() {
  knob_state_t state;
  static knob_pin_t pin;  // Make static to prevent destruction
  pin.clk = PIN_KNOB_CLK;
  pin.dt = PIN_KNOB_DT;
  pin.sw = PIN_KNOB_SW;
  state.pin = &pin;
  state.state = KNOB_IDLE;
  state.last_clk = HIGH;  // Initialize with pullup default
  state.last_rotation_time = 0;  // Initialize debounce timer
  return state;
}

void init_knob_pins(knob_state_t *knob_state) {
  Serial.print("Initializing knob - CLK: ");
  Serial.print(knob_state->pin->clk);
  Serial.print(", DT: ");
  Serial.print(knob_state->pin->dt);
  Serial.print(", SW: ");
  Serial.println(knob_state->pin->sw);
  
  pinMode(knob_state->pin->clk, INPUT_PULLUP);
  pinMode(knob_state->pin->dt, INPUT_PULLUP);
  pinMode(knob_state->pin->sw, INPUT_PULLUP);
  
  delay(10);  // Let pins stabilize
  knob_state->last_clk = digitalRead(knob_state->pin->clk);
  
  Serial.print("Knob initialized - Initial CLK: ");
  Serial.println(knob_state->last_clk);
}

#endif // __KNOBSTATE_H__
