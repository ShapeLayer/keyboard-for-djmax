#ifndef __CONFIG_H__
#define __CONFIG_H__
#include <Keyboard.h>
#include "const.h"

/**
 * Configuration
 * 
 * If you don't want to use a specific pin for keyout or want to disable a specific key,
 * just set the pin to UNDEFINED.
 * i.e. #define KEYOUT_TRACK_1 UNDEFINED
 */

#define KNOB_IS_ENABLED true
#define DISPLAY_IS_ENABLED true

/**
 * Matrix constructed key switch pins
 * 
 * TRACK_SIDE_L = PIN_TRACK_L & PIN_TRACK_SIDE
 * TRACK_5 = PIN_TRACK_R & PIN_TRACK_1
 */
// Key Row in Key Matrix
#define PIN_TRACK_L 3
#define PIN_TRACK_R 4

// Key Column in Key Matrix
#define PIN_TRACK_SIDE 5
#define PIN_TRACK_1 6
#define PIN_TRACK_2 7
#define PIN_TRACK_3 8
#define PIN_TRACK_CENTER 9

// Knob Pins
#define PIN_KNOB_CLK 10
#define PIN_KNOB_DT 11
#define PIN_KNOB_SW 12

// Display Pins
#define PIN_DISPLAY_SDA 13
#define PIN_DISPLAY_SCL 14

/**
 * Keyboard input to connected device
 */
#define KEYOUT_TRACK_SIDE_L KEY_LEFT_SHIFT
#define KEYOUT_TRACK_1 'a'
#define KEYOUT_TRACK_2 's'
#define KEYOUT_TRACK_3 'd'
#define KEYOUT_TRACK_L 'f'
#define KEYOUT_TRACK_R 'j'
#define KEYOUT_TRACK_4 'k'
#define KEYOUT_TRACK_5 'l'
#define KEYOUT_TRACK_6 ';'
#define KEYOUT_TRACK_SIDE_R KEY_RIGHT_SHIFT

#define KEYOUT_KNOB_CW '1'
#define KEYOUT_KNOB_CCW '2'

// Threashold for preventing chattering
#define DEBOUNCE_DELAY 5  // (ms)

// Slicing value for last_changed to prevent overflow
#define LAST_CHANGED_SLICING 4000000000
#define MILLIS_SLICING 4000000000

// Display configuration
// TODO: Improving a content of display required.
#define PLACEHOLDER_DISPLAY_TEXT_ON_INIT "Hello"
#define DISPLAY_TEMPLATE_ON_KNOB_ROTATE_CW "+1"
#define DISPLAY_TEMPLATE_ON_KNOB_ROTATE_CCW "-1"

#define DISPLAY_BACK_TO_IDLE_TIMEOUT 5000  // (ms)

#endif  // __CONFIG_H__
