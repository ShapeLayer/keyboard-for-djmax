#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "keystate.h"
#include "knobstate.h"

// Definitions
#define KEY_IS_PRESSED(state, key) \
  ((state)->key_pressed_left & (1 << (key)) || (state)->key_pressed_right & (1 << (key - 5)))

#define MODULE_ID_KEY 0
#define MODULE_ID_DISPLAY 1
#define MODULE_ID_KNOB 2
#define APPEND_DISPLAY_REQUESTED_MODULE(state, module_id) \
  ((state)->last_display_requested_modules |= (1 << (module_id)))
#define CLEAR_DISPLAY_REQUESTED_MODULE(state) \
  ((state)->last_display_requested_modules = 0)
#define IS_DISPLAY_REQUESTED_MODULE(state, module_id) \
  ((state)->last_display_requested_modules & (1 << (module_id)))
#define IS_DISPLAY_REQUESTED_MODULE_ANY(state) \
  ((state)->last_display_requested_modules != 0)

typedef struct {
  unsigned short last_display_requested_modules;
  unsigned short key_pressed_left;
  unsigned short key_pressed_right;
  knob_state_e   knob_rotate_dir;
  unsigned long  last_event_time;
} context_t;

context_t new_context();

// Implementations
context_t new_context() {
  context_t state;
  state.last_display_requested_modules = 0;
  state.key_pressed_left = 0;
  state.key_pressed_right = 0;
  state.knob_rotate_dir = KNOB_IDLE;
  state.last_event_time = 0;
  return state;
}

/*
  // Disabled: Request must be call micro() to update last changed time
  // But in the calling scenario, it concerns overhead (calling a lot of times)
  // The logic of below function is integrated in `process_key_pressed`@keypress.h
void request_display_update_key(context_t *state, key_state_t *key_state, int key_id) {
  state->last_display_requested = MODULE_TYPE_KEY;
  if (key_id < 5) {
    state->key_pressed_left |= (1 << key_id);
  } else {
    state->key_pressed_right |= (1 << (key_id - 5));
  }
}
  */

#endif  // __CONTEXT_H__
