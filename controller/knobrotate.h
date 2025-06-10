#ifndef __KNOBROTATE_H__
#define __KNOBROTATE_H__

#include <Keyboard.h>

#include "config.h"
#include "context.h"
#include "knobstate.h"
#include "utils.h"

// Definitions
void update_knob_state(context_t *, knob_state_t *);
void proc_knob_handler(context_t *, knob_state_t *);
void process_knob_rotated(knob_state_e state);
void debug_knob_pins(knob_state_t *);  // For debugging

// Implementations
void update_knob_state(context_t *context, knob_state_t *knob_state) {
  int curr_clk = digitalRead(knob_state->pin->clk);
  
  // Only process on CLK falling edge (more reliable for most encoders)
  if (curr_clk == HIGH || knob_state->last_clk == LOW) {
    knob_state->last_clk = curr_clk;
    return;
  }

  // Check for debounce period (prevent multiple detections from one rotation)
  unsigned long now = millis();
  if (now - knob_state->last_rotation_time < 5) {  // 50ms debounce
    knob_state->last_clk = curr_clk;
    return;
  }

  // CLK went from HIGH to LOW - actual rotation detected
  int curr_dt = digitalRead(knob_state->pin->dt);
  
  unsigned long now_millis_s = MILLIS_S();
  context->last_event_time = now_millis_s;
  knob_state->last_rotation_time = now;
  
  Serial.print("Knob rotation detected - CLK: ");
  Serial.print(curr_clk);
  Serial.print(", DT: ");
  Serial.print(curr_dt);
  
  if (curr_dt != curr_clk) {
    knob_state->state = KNOB_ROTATE_CW;
    context->knob_rotate_dir = KNOB_ROTATE_CW;
    Serial.println(" -> CW");
  } else {
    knob_state->state = KNOB_ROTATE_CCW;
    context->knob_rotate_dir = KNOB_ROTATE_CCW;
    Serial.println(" -> CCW");
  }
  
  // Only request display update when there's actual rotation
  APPEND_DISPLAY_REQUESTED_MODULE(context, MODULE_ID_KNOB);
  
  knob_state->last_clk = curr_clk;
}

void proc_knob_handler(context_t *context, knob_state_t *knob_state) {
  #if KNOB_IS_ENABLED
  update_knob_state(context, knob_state);
  
  // Only process if there's an actual rotation, then reset state
  if (knob_state->state != KNOB_IDLE) {
    process_knob_rotated(knob_state->state);
    // Reset state to prevent continuous sending
    knob_state->state = KNOB_IDLE;
    context->knob_rotate_dir = KNOB_IDLE;
  }
  #endif  // KNOB_IS_ENABLED
}

void process_knob_rotated(knob_state_e state) {
  switch (state) {
    case KNOB_ROTATE_CW:
      Serial.println("Sending CW key");
      Keyboard.write(KEYOUT_KNOB_CW);
      break;
    case KNOB_ROTATE_CCW:
      Serial.println("Sending CCW key");
      Keyboard.write(KEYOUT_KNOB_CCW);
      break;
    case KNOB_IDLE:
    default:
      break;
  }
}

void debug_knob_pins(knob_state_t *knob_state) {
  static unsigned long last_debug = 0;
  unsigned long now = millis();
  
  // Print debug info every 2 seconds
  if (now - last_debug > 2000) {
    int clk = digitalRead(knob_state->pin->clk);
    int dt = digitalRead(knob_state->pin->dt);
    int sw = digitalRead(knob_state->pin->sw);
    
    Serial.print("Knob pins - CLK: ");
    Serial.print(clk);
    Serial.print(", DT: ");
    Serial.print(dt);
    Serial.print(", SW: ");
    Serial.println(sw);
    
    last_debug = now;
  }
}

#endif // __KNOBROTATE_H__
