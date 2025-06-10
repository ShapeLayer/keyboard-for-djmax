#ifndef __DISPLAYHANDLE_H__
#define __DISPLAYHANDLE_H__

#include "config.h"
#include "displaystate.h"
#include "context.h"
#include "utils.h"

// Definitions
void make_display_idle(display_state_t *);
void clear_display(display_state_t *);
void init_display_pins(display_state_t *);
void _proc_last_request(context_t *, display_state_t *);
void print_display(display_state_t *, const String &);
void proc_display_handler(context_t *, display_state_t *);

// Implementations
void make_display_idle(display_state_t *display_state) {
  // placeholder
  clear_display(display_state);
}

void clear_display(display_state_t *display_state) {
  if (display_state->u8g2 != nullptr) {
    display_state->u8g2->clearBuffer();
    display_state->is_cleared = true;
  }
}

/**
 * display_state->u8g2 must not be nullptr.
 */
void _proc_last_request(
  context_t *context,
  display_state_t *display_state
) {
  String buffer = "";  // Key
  if (IS_DISPLAY_REQUESTED_MODULE(context, MODULE_ID_KEY)) {
    display_state->u8g2->clearBuffer();
    display_state->u8g2->setCursor(0, 10);
    for (int i = 0; i < 5; i++) {
      if (context->key_pressed_left & (1 << i)) {
        buffer += String(i) + " ";
      }
    }
    for (int i = 5; i < 10; i++) {
      if (context->key_pressed_right & (1 << (i - 5))) {
        buffer += String(i) + " ";
      }
    }
  }
  // Display
  // Knob
  if (IS_DISPLAY_REQUESTED_MODULE(context, MODULE_ID_KNOB)) {
    knob_state_e direction = context->knob_rotate_dir;
    
    switch (direction) {
      case KNOB_ROTATE_CW:
        buffer += " CW";
        break;
      case KNOB_ROTATE_CCW:
        buffer += "CCW";
        break;
      case KNOB_IDLE:
      default:
        buffer += "  I";
        break;
    }
  }

  print_display(display_state, buffer);
  CLEAR_DISPLAY_REQUESTED_MODULE(context);
  display_state->is_cleared = false;
}

void print_display(
  display_state_t *display_state,
  const String &text
) {
  if (display_state->u8g2 == nullptr) { return; }
  display_state->u8g2->clearBuffer();
  display_state->u8g2->setCursor(0, 10);
  display_state->u8g2->print(text);
  display_state->u8g2->sendBuffer();

  display_state->is_cleared = false;
}

void proc_display_handler(
  context_t *context,
  display_state_t *display_state
) {
  if (display_state->u8g2 == nullptr) { 
    Serial.println("Display u8g2 is nullptr");
    return; 
  }
  if (IS_DISPLAY_REQUESTED_MODULE_ANY(context)) {
    Serial.println("Display update requested");
    _proc_last_request(context, display_state);
  } else {
    if (time_s_diff(
        context->last_event_time,
        MILLIS_S()
      ) > DISPLAY_BACK_TO_IDLE_TIMEOUT) {
      clear_display(display_state);
    }
  }
}

void init_display_pins(display_state_t *display_state) {
  Serial.print("Initializing display - SDA: ");
  Serial.print(display_state->pin->sda);
  Serial.print(", SCL: ");
  Serial.println(display_state->pin->scl);
  
  display_state->u8g2 = new U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C(
    U8G2_R0,
    display_state->pin->scl,
    display_state->pin->sda,
    U8X8_PIN_NONE
  );
  
  if (display_state->u8g2 != nullptr) {
    display_state->u8g2->begin();
    display_state->u8g2->setFont(u8g2_font_ncenB08_tr);
    clear_display(display_state);
    
    // Show initial text
    print_display(display_state, "DJMAX Ready");
    Serial.println("Display initialized successfully");
  } else {
    Serial.println("Failed to initialize display");
  }
}

#endif  // __DISPLAYHANDLE_H__
