#include <Keyboard.h>
#include "const.h"
#include "context.h"
#include "config.h"
#include "displaystate.h"
#include "displayhandle.h"
#include "keystate.h"
#include "keypress.h"
#include "knobstate.h"
#include "knobrotate.h"

#include "config.h"

context_t context;
display_state_t display_state;
key_set_state_t key_set_state;
knob_state_t knob_state;

void init_pins();

void setup() {
  context = new_context();
  display_state = new_display_state();
  key_set_state = new_key_set_state();
  knob_state = new_knob_state();

  init_display_pins(&display_state);
  init_key_pins();
  init_knob_pins(&knob_state);
}

void loop() {
  proc_keys_handler(&context, &key_set_state);
  #if KNOB_IS_ENABLED
  proc_knob_handler(&context, &knob_state);
  #endif  // KNOB_IS_ENABLED
}
