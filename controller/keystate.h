#ifndef __KEYSTATE_H__
#define __KEYSTATE_H__

#include "config.h"
#include "utils.h"

// Definitions
#define KEYID_TRACK_SIDE_L 0
#define KEYID_TRACK_1 1
#define KEYID_TRACK_2 2
#define KEYID_TRACK_3 3
#define KEYID_TRACK_L 4
#define KEYID_TRACK_R 5
#define KEYID_TRACK_4 6
#define KEYID_TRACK_5 7
#define KEYID_TRACK_6 8
#define KEYID_TRACK_SIDE_R 9

#define GET_KEYID_OUTPUT(key) \
  ((key) == KEYOUT_TRACK_SIDE_L ? KEYID_TRACK_SIDE_L : \
   (key) == KEYOUT_TRACK_1 ? KEYID_TRACK_1 : \
   (key) == KEYOUT_TRACK_2 ? KEYID_TRACK_2 : \
   (key) == KEYOUT_TRACK_3 ? KEYID_TRACK_3 : \
   (key) == KEYOUT_TRACK_L ? KEYID_TRACK_L : \
   (key) == KEYOUT_TRACK_R ? KEYID_TRACK_R : \
   (key) == KEYOUT_TRACK_4 ? KEYID_TRACK_4 : \
   (key) == KEYOUT_TRACK_5 ? KEYID_TRACK_5 : \
   (key) == KEYOUT_TRACK_6 ? KEYID_TRACK_6 : \
   (key) == KEYOUT_TRACK_SIDE_R ? KEYID_TRACK_SIDE_R : -1)

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
void init_key_pins();
INLINE void update_last_changed(key_state_t *, unsigned int);
INLINE bool is_in_debounce_period(key_state_t *, unsigned long);

// Implementations
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

void init_key_pins() {
  // Row
  #if PIN_TRACK_L != UNDEFINED
  pinMode(PIN_TRACK_L, OUTPUT);
  digitalWrite(PIN_TRACK_L, HIGH);
  #endif  // PIN_TRACK_L != UNDEFINED
  #if PIN_TRACK_R != UNDEFINED
  pinMode(PIN_TRACK_R, OUTPUT);
  digitalWrite(PIN_TRACK_R, HIGH);
  #endif  // PIN_TRACK_R != UNDEFINED

  // Column
  #if PIN_TRACK_SIDE != UNDEFINED
  pinMode(PIN_TRACK_SIDE, INPUT_PULLUP);
  #endif  // PIN_TRACK_SIDE != UNDEFINED
  #if PIN_TRACK_1 != UNDEFINED
  pinMode(PIN_TRACK_1, INPUT_PULLUP);
  #endif  // PIN_TRACK_1 != UNDEFINED
  #if PIN_TRACK_2 != UNDEFINED
  pinMode(PIN_TRACK_2, INPUT_PULLUP);
  #endif  // PIN_TRACK_2 != UNDEFINED
  #if PIN_TRACK_3 != UNDEFINED
  pinMode(PIN_TRACK_3, INPUT_PULLUP);
  #endif  // PIN_TRACK_3 != UNDEFINED
  #if PIN_TRACK_CENTER != UNDEFINED
  pinMode(PIN_TRACK_CENTER, INPUT_PULLUP);
  #endif  // PIN_TRACK_CENTER != UNDEFINED
}

INLINE void update_last_changed(key_state_t *state, unsigned int value) {
  time_slice(&(state->last_changed));
}

INLINE bool is_in_debounce_period(key_state_t *state, unsigned long now) {
  return time_s_diff(state->last_changed, now) < DEBOUNCE_DELAY;
}

#endif  // __KEYSTATE_H__
