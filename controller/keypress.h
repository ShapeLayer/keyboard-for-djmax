#ifndef __KEYPRESS_H__
#define __KEYPRESS_H__

#include <Keyboard.h>

#include "config.h"
#include "keystate.h"
#include "keypress.h"
#include "utils.h"

// Definitions
void proc_keys_handler(context_t *, key_set_state_t *);
bool process_key_pressed(context_t *, key_state_t *, bool, unsigned long, int);

// Implementations
void proc_keys_handler(context_t *context, key_set_state_t *key_set_state) {
  unsigned long now = MILLIS_S();
  bool is_changed = false;
    // Left track
  #if PIN_TRACK_L != UNDEFINED
  digitalWrite(PIN_TRACK_L, LOW);
  delayMicroseconds(10);  // Small delay to ensure pin state is stable
  #if PIN_TRACK_SIDE != UNDEFINED && KEYOUT_TRACK_SIDE_L != UNDEFINED
  is_changed |= process_key_pressed(
    context,
    &(key_set_state->track_side_l),
    !(bool)digitalRead(PIN_TRACK_SIDE),
    now,
    KEYID_TRACK_SIDE_L
  );
  #endif  // PIN_TRACK_SIDE != UNDEFINED && KEYOUT_TRACK_SIDE_L != UNDEFINED
  #if PIN_TRACK_1 != UNDEFINED && KEYOUT_TRACK_1 != UNDEFINED
  is_changed |= process_key_pressed(
    context,
    &(key_set_state->track_1),
    !(bool)digitalRead(PIN_TRACK_1),
    now,
    KEYID_TRACK_1
  );
  #endif  // PIN_TRACK_1 != UNDEFINED && KEYOUT_TRACK_1 != UNDEFINED
  #if PIN_TRACK_2 != UNDEFINED && KEYOUT_TRACK_2 != UNDEFINED
  is_changed |= process_key_pressed(
    context,
    &(key_set_state->track_2),
    !(bool)digitalRead(PIN_TRACK_2),
    now,
    KEYID_TRACK_2
  );
  #endif  // PIN_TRACK_2 != UNDEFINED && KEYOUT_TRACK_2 != UNDEFINED
  #if PIN_TRACK_3 != UNDEFINED && KEYOUT_TRACK_3 != UNDEFINED
  is_changed |= process_key_pressed(
    context,
    &(key_set_state->track_3),
    !(bool)digitalRead(PIN_TRACK_3),
    now,
    KEYID_TRACK_3
  );
  #endif  // PIN_TRACK_3 != UNDEFINED && KEYOUT_TRACK_3 != UNDEFINED
  #if PIN_TRACK_CENTER != UNDEFINED && KEYOUT_TRACK_L != UNDEFINED
  is_changed |= process_key_pressed(
    context,
    &(key_set_state->track_l),
    !(bool)digitalRead(PIN_TRACK_CENTER),
    now,
    KEYID_TRACK_L
  );
  #endif  // PIN_TRACK_CENTER != UNDEFINED && KEYOUT_TRACK_L != UNDEFINED
  digitalWrite(PIN_TRACK_L, HIGH);
  #endif  // PIN_TRACK_L != UNDEFINED
  // Right track
  #if PIN_TRACK_R != UNDEFINED
  digitalWrite(PIN_TRACK_R, LOW);
  delayMicroseconds(10);  // Small delay to ensure pin state is stable
  #if PIN_TRACK_SIDE != UNDEFINED && KEYOUT_TRACK_SIDE_R != UNDEFINED
  is_changed |= process_key_pressed(
    context,
    &(key_set_state->track_side_r),
    !(bool)digitalRead(PIN_TRACK_SIDE),
    now,
    KEYID_TRACK_SIDE_R
  );
  #endif  // PIN_TRACK_SIDE != UNDEFINED && KEYOUT_TRACK_SIDE_R != UNDEFINED
  #if PIN_TRACK_1 != UNDEFINED && KEYOUT_TRACK_4 != UNDEFINED
  is_changed |= process_key_pressed(
    context,
    &(key_set_state->track_4),
    !(bool)digitalRead(PIN_TRACK_1),
    now,
    KEYID_TRACK_4
  );
  #endif  // PIN_TRACK_1 != UNDEFINED && KEYOUT_TRACK_4 != UNDEFINED
  #if PIN_TRACK_2 != UNDEFINED && KEYOUT_TRACK_5 != UNDEFINED
  is_changed |= process_key_pressed(
    context,
    &(key_set_state->track_5),
    !(bool)digitalRead(PIN_TRACK_2),
    now,
    KEYID_TRACK_5
  );
  #endif  // PIN_TRACK_2 != UNDEFINED && KEYOUT_TRACK_5 != UNDEFINED
  #if PIN_TRACK_3 != UNDEFINED && KEYOUT_TRACK_6 != UNDEFINED
  is_changed |= process_key_pressed(
    context,
    &(key_set_state->track_6),
    !(bool)digitalRead(PIN_TRACK_3),
    now,
    KEYID_TRACK_6
  );
  #endif  // PIN_TRACK_3 != UNDEFINED && KEYOUT_TRACK_6 != UNDEFINED
  #if PIN_TRACK_CENTER != UNDEFINED && KEYOUT_TRACK_R != UNDEFINED
  is_changed |= process_key_pressed(
    context,
    &(key_set_state->track_r),
    !(bool)digitalRead(PIN_TRACK_CENTER),
    now,
    KEYID_TRACK_R
  );
  #endif  // PIN_TRACK_CENTER != UNDEFINED && KEYOUT_TRACK_R != UNDEFINED
  digitalWrite(PIN_TRACK_R, HIGH);
  #endif  // PIN_TRACK_R != UNDEFINED
  if (is_changed) {
    context->last_event_time = now;
  }
}

bool process_key_pressed(context_t *context, key_state_t *state, bool is_pressed, unsigned long now, int context_pressed_flag_index) {
  /**
   * @returns bool is_changed
   */
  if (is_in_debounce_period(state, now)) {
    update_last_changed(state, now);
    return false;
  }
  // Update context_t
  if (context_pressed_flag_index < 5) {
    // Left track
    if (is_pressed) {
      context->key_pressed_left |= (1 << context_pressed_flag_index);
    } else {
      context->key_pressed_left &= ~(1 << context_pressed_flag_index);
    }
  } else {
    // Right track
    if (is_pressed) {
      context->key_pressed_right |= (1 << (context_pressed_flag_index - 5));
    } else {
      context->key_pressed_right &= ~(1 << (context_pressed_flag_index - 5));
    }
  }  if (state->pressed != is_pressed) {
    state->pressed = is_pressed;
    update_last_changed(state, now);
    Serial.print("Key change - ID: ");
    Serial.print(context_pressed_flag_index);
    Serial.print(", Key: ");
    if (state->key >= 32 && state->key <= 126) {
      Serial.print((char)state->key);
    } else {
      Serial.print("0x");
      Serial.print(state->key, HEX);
    }
    Serial.print(", Pressed: ");
    Serial.println(is_pressed);
    if (is_pressed) {
      Keyboard.press(state->key);
    } else {
      Keyboard.release(state->key);
    }
    return true;
  }
  return false;
}

#endif // __KEYPRESS_H__
