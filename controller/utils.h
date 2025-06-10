#ifndef __UTILS_H__
#define __UTILS_H__

#include "config.h"

// unsigned long
#define MILLIS_S() millis() % MILLIS_SLICING
#define MICROS_S() micros() % MILLIS_SLICING

INLINE void time_slice(unsigned long *time) {
  if (*time >= MILLIS_SLICING) {
    *time -= MILLIS_SLICING;
  }
}

INLINE unsigned long time_s_diff(unsigned long before, unsigned long after) {
  unsigned long diff;
  if (before <= after) {
    diff = after - before;
  } else {
    diff = MILLIS_SLICING + after - before;
  }
  return diff;
}

#endif  // __UTILS_H__
