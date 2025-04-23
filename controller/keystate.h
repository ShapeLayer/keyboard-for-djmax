#ifndef __KEYSTATE_H__
#define __KEYSTATE_H__

#include "config.h"

typedef struct {
  uint8_t key;
  unsigned long last_changed;
  bool pressed;
} key_state_t;

typedef struct {
  key_state_t track_side_l;
  key_state_t track_1;
  key_state_t track_2;
  key_state_t track_3;
  key_state_t track_l;
  key_state_t track_r;
  key_state_t track_4;
  key_state_t track_5;
  key_state_t track_6;
  key_state_t track_side_r;
} key_set_state_t;

key_state_t new_key_state(uint8_t);
key_set_state_t new_key_set_state();
INLINE void update_last_changed(key_state_t *, unsigned int);
INLINE bool is_in_debounce_period(key_state_t *, unsigned long);


key_state_t new_key_state(uint8_t key) {
  key_state_t state;
  state.key = key;
  state.last_changed = 0;
  state.pressed = false;
  return state;
};

key_set_state_t new_key_set_state() {
  key_set_state_t set_state;
  set_state.track_side_l = new_key_state(KEYOUT_TRACK_SIDE_L);
  set_state.track_1 = new_key_state(KEYOUT_TRACK_1);
  set_state.track_2 = new_key_state(KEYOUT_TRACK_2);
  set_state.track_3 = new_key_state(KEYOUT_TRACK_3);
  set_state.track_l = new_key_state(KEYOUT_TRACK_L);
  set_state.track_r = new_key_state(KEYOUT_TRACK_R);
  set_state.track_4 = new_key_state(KEYOUT_TRACK_4);
  set_state.track_5 = new_key_state(KEYOUT_TRACK_5);
  set_state.track_6 = new_key_state(KEYOUT_TRACK_6);
  set_state.track_side_r = new_key_state(KEYOUT_TRACK_SIDE_R);
  return set_state;
};

INLINE void update_last_changed(key_state_t *state, unsigned int value) {
  state->last_changed = value % LAST_CHANGED_SLICING;
  return;
}

INLINE bool is_in_debounce_period(key_state_t *state, unsigned long now) {
  unsigned long diff;
  if (state->last_changed <= now) {
    diff = now - state->last_changed;
  } else {
    diff = LAST_CHANGED_SLICING + now - state->last_changed;
  }
  return (now - state->last_changed) < DEBOUNCE_DELAY;
}

#endif  // __KEYSTATE_H__
