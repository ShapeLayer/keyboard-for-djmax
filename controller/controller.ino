#include <Keyboard.h>
#include "const.h"
#include "keystate.h"

#include "config.h"

key_set_state_t key_set_state;

void init_pins();
void process_key_pressed(key_state_t *, bool);

void setup() {
  init_pins();

  key_set_state = new_key_set_state();
}

void loop() {
  // Left track
  #if PIN_TRACK_L != UNDEFINED
  digitalWrite(PIN_TRACK_L, LOW);
  #if PIN_TRACK_SIDE != UNDEFINED && KEYOUT_TRACK_SIDE_L != UNDEFINED
  process_key_pressed(
    &(key_set_state.track_side_l),
    (bool)digitalRead(PIN_TRACK_SIDE)
  );
  #endif  // PIN_TRACK_SIDE != UNDEFINED && KEYOUT_TRACK_SIDE_L != UNDEFINED
  #if PIN_TRACK_1 != UNDEFINED && KEYOUT_TRACK_1 != UNDEFINED
  process_key_pressed(
    &(key_set_state.track_1),
    (bool)digitalRead(PIN_TRACK_1)
  );
  #endif  // PIN_TRACK_1 != UNDEFINED && KEYOUT_TRACK_1 != UNDEFINED
  #if PIN_TRACK_2 != UNDEFINED && KEYOUT_TRACK_2 != UNDEFINED
  process_key_pressed(
    &(key_set_state.track_2),
    (bool)digitalRead(PIN_TRACK_2)
  );
  #endif  // PIN_TRACK_2 != UNDEFINED && KEYOUT_TRACK_2 != UNDEFINED
  #if PIN_TRACK_3 != UNDEFINED && KEYOUT_TRACK_3 != UNDEFINED
  process_key_pressed(
    &(key_set_state.track_3),
    (bool)digitalRead(PIN_TRACK_3)
  );
  #endif  // PIN_TRACK_3 != UNDEFINED && KEYOUT_TRACK_3 != UNDEFINED
  #if PIN_TRACK_CENTER != UNDEFINED && KEYOUT_TRACK_L != UNDEFINED
  process_key_pressed(
    &(key_set_state.track_l),
    (bool)digitalRead(PIN_TRACK_CENTER)
  );
  #endif  // PIN_TRACK_CENTER != UNDEFINED && KEYOUT_TRACK_L != UNDEFINED
  digitalWrite(PIN_TRACK_L, HIGH);
  #endif  // PIN_TRACK_L != UNDEFINED

  // Right track
  #if PIN_TRACK_R != UNDEFINED
  digitalWrite(PIN_TRACK_R, LOW);
  #if PIN_TRACK_SIDE != UNDEFINED && KEYOUT_TRACK_SIDE_R != UNDEFINED
  process_key_pressed(
    &(key_set_state.track_side_r),
    (bool)digitalRead(PIN_TRACK_SIDE)
  );
  #endif  // PIN_TRACK_SIDE != UNDEFINED && KEYOUT_TRACK_SIDE_R != UNDEFINED
  #if PIN_TRACK_1 != UNDEFINED && KEYOUT_TRACK_4 != UNDEFINED
  process_key_pressed(
    &(key_set_state.track_4),
    (bool)digitalRead(PIN_TRACK_1)
  );
  #endif  // PIN_TRACK_1 != UNDEFINED && KEYOUT_TRACK_4 != UNDEFINED
  #if PIN_TRACK_2 != UNDEFINED && KEYOUT_TRACK_5 != UNDEFINED
  process_key_pressed(
    &(key_set_state.track_5),
    (bool)digitalRead(PIN_TRACK_2)
  );
  #endif  // PIN_TRACK_2 != UNDEFINED && KEYOUT_TRACK_5 != UNDEFINED
  #if PIN_TRACK_3 != UNDEFINED && KEYOUT_TRACK_6 != UNDEFINED
  process_key_pressed(
    &(key_set_state.track_6),
    (bool)digitalRead(PIN_TRACK_3)
  );
  #endif  // PIN_TRACK_3 != UNDEFINED && KEYOUT_TRACK_6 != UNDEFINED
  #if PIN_TRACK_CENTER != UNDEFINED && KEYOUT_TRACK_R != UNDEFINED
  process_key_pressed(
    &(key_set_state.track_r),
    (bool)digitalRead(PIN_TRACK_CENTER)
  );
  #endif  // PIN_TRACK_CENTER != UNDEFINED && KEYOUT_TRACK_R != UNDEFINED
  digitalWrite(PIN_TRACK_R, HIGH);
  #endif  // PIN_TRACK_R != UNDEFINED
}


void init_pins() {
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

void process_key_pressed(key_state_t *state, bool is_pressed) {
  unsigned long now = micros();
  if (is_in_debounce_period(state, now)) {
    update_last_changed(state, now);
    return;
  }

  if (state->pressed != is_pressed) {
    state->pressed = is_pressed;
    update_last_changed(state, now);
    if (is_pressed) {
      Keyboard.press(state->key);
    } else {
      Keyboard.release(state->key);
    }
  }
}
