#ifndef __KNOBROTATE_H__
#define __KNOBROTATE_H__

#include <Keyboard.h>

#include "config.h"
#include "context.h"
#include "knobstate.h"

// Definitions
void update_knob_state(context_t *, knob_state_t *);
void proc_knob_handler(context_t *, knob_state_t *);
void process_knob_rotated(knob_state_e state);

// Implementations
void update_knob_state(context_t *context, knob_state_t *knob_state) {
  int curr_clk = digitalRead(knob_state->pin->clk);
  if (curr_clk == LOW && knob_state->last_clk == LOW) { return; }

  unsigned long now = MILLIS_S();
  context->last_event_time = now;
  APPEND_DISPLAY_REQUESTED_MODULE(context, MODULE_ID_KNOB);

  if (curr_clk == HIGH && knob_state->last_clk == LOW) {
    int curr_dt = digitalRead(knob_state->pin->dt);
    if (curr_dt != curr_clk) {
      knob_state->state = KNOB_ROTATE_CW;
      context->knob_rotate_dir = KNOB_ROTATE_CW;
    } else {
      knob_state->state = KNOB_ROTATE_CCW;
      context->knob_rotate_dir = KNOB_ROTATE_CCW;
    }
  } else {
    knob_state->state = KNOB_IDLE;
    context->knob_rotate_dir = KNOB_IDLE;
  }
  knob_state->last_clk = curr_clk;
}

void proc_knob_handler(context_t *context, knob_state_t *knob_state) {
  #if KNOB_IS_ENABLED
  update_knob_state(context, knob_state);
  process_knob_rotated(knob_state->state);
  #endif  // KNOB_IS_ENABLED
}

void process_knob_rotated(knob_state_e state) {
  switch (state) {
    case KNOB_ROTATE_CW:
      Keyboard.write(KEYOUT_KNOB_CW);
      break;
    case KNOB_ROTATE_CCW:
      Keyboard.write(KEYOUT_KNOB_CCW);
      break;
    case KNOB_IDLE:
    default:
      break;
  }
}

#endif // __KNOBROTATE_H__
