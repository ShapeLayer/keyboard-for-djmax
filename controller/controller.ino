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
  digitalWrite(PIN_TRACK_L, LOW);
  process_key_pressed(
    &(key_set_state.track_side_l),
    (bool)digitalRead(PIN_TRACK_SIDE)
  );
  process_key_pressed(
    &(key_set_state.track_1),
    (bool)digitalRead(PIN_TRACK_1)
  );
  process_key_pressed(
    &(key_set_state.track_2),
    (bool)digitalRead(PIN_TRACK_2)
  );
  process_key_pressed(
    &(key_set_state.track_3),
    (bool)digitalRead(PIN_TRACK_3)
  );
  process_key_pressed(
    &(key_set_state.track_l),
    (bool)digitalRead(PIN_TRACK_CENTER)
  );
  digitalWrite(PIN_TRACK_L, HIGH);
  // Right track
  digitalWrite(PIN_TRACK_R, LOW);
  process_key_pressed(
    &(key_set_state.track_side_r),
    (bool)digitalRead(PIN_TRACK_SIDE)
  );
  process_key_pressed(
    &(key_set_state.track_4),
    (bool)digitalRead(PIN_TRACK_1)
  );
  process_key_pressed(
    &(key_set_state.track_5),
    (bool)digitalRead(PIN_TRACK_2)
  );
  process_key_pressed(
    &(key_set_state.track_6),
    (bool)digitalRead(PIN_TRACK_3)
  );
  process_key_pressed(
    &(key_set_state.track_r),
    (bool)digitalRead(PIN_TRACK_CENTER)
  );
  digitalWrite(PIN_TRACK_R, HIGH);
}


void init_pins() {
  // Row
  pinMode(PIN_TRACK_L, OUTPUT);
  pinMode(PIN_TRACK_R, OUTPUT);
  digitalWrite(PIN_TRACK_L, HIGH);
  digitalWrite(PIN_TRACK_R, HIGH);
  // Column
  pinMode(PIN_TRACK_SIDE, INPUT_PULLUP);
  pinMode(PIN_TRACK_1, INPUT_PULLUP);
  pinMode(PIN_TRACK_2, INPUT_PULLUP);
  pinMode(PIN_TRACK_3, INPUT_PULLUP);
  pinMode(PIN_TRACK_CENTER, INPUT_PULLUP);
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
