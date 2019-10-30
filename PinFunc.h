//
// Created by mpapis on 21.10.19.
//

#include "state.h"

/* Example use:
 * State light1_raw = State(InputFunctions,       &pin_nr)
 * State light2_raw = State(InputPullupFunctions, &pin_nr)
 */

typedef byte pin_data;

void pin_init_input(State &_state, pin_data *pin) {
  pinMode(*pin, INPUT);
}

void pin_init_input_pullup(State &_state, pin_data *pin) {
  pinMode(*pin, INPUT_PULLUP);
}

byte pin_read(State &_state, pin_data *pin) {
  return digitalRead(*pin);
}

byte pin_read_invert(State &_state, pin_data *pin) {
  return !digitalRead(*pin);
}

const StateFunctions InputFunctions       = StateFunctions(&pin_init_input,        &pin_read,        nullptr);
const StateFunctions InputPullupFunctions = StateFunctions(&pin_init_input_pullup, &pin_read_invert, nullptr);
