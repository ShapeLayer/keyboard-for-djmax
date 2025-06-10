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
} knob_state_t;

knob_state_t new_knob_state();
void init_knob_pins(knob_state_t *);

// Implementations
knob_state_t new_knob_state() {
  knob_state_t state;
  knob_pin_t pin;
  pin.clk = PIN_KNOB_CLK;
  pin.dt = PIN_KNOB_DT;
  pin.sw = PIN_KNOB_SW;
  state.pin = &pin;
  state.state = KNOB_IDLE;
  return state;
}

void init_knob_pins(knob_state_t *knob_state) {
  pinMode(knob_state->pin->clk, INPUT_PULLUP);
  pinMode(knob_state->pin->dt, INPUT_PULLUP);
  pinMode(knob_state->pin->sw, INPUT_PULLUP);
  knob_state->last_clk = digitalRead(knob_state->pin->clk);
}

#endif // __KNOBSTATE_H__
