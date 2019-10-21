//
// Created by mpapis on 21.10.19.
//

void pin_init_input(byte pin) {
  pinMode(pin, INPUT);
}

void pin_init_input_pullup(byte pin) {
  pinMode(pin, INPUT_PULLUP);
}

byte pin_read(byte pin) {
  return digitalRead(pin);
}

byte pin_read_invert(byte pin) {
  return !digitalRead(pin);
}
