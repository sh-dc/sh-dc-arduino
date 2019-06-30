//
// Created by mpapis on 30.06.19.
//

#ifndef SHDC_STRUCTURES_H
#define SHDC_STRUCTURES_H

struct TARGETS
{
  // user defined
  const byte     output_pin;
  const uint8_t  rule;
  const uint32_t rule_value;

  // used internally, do not define!
  uint32_t rule_data;
};

// bit mask for the SWITCHES flags
#define FLAG_NONE     0
#define FLAG_BISTABLE B1 // monostable otherwise

struct SWITCHES {
  // user defined
  const Button button;
  const byte   flags;

  // used internally, do not define!
  byte state;
};

struct CONNECTIONS
{
  // user defined
  const byte source;
  const byte target;
};

#endif //SHDC_STRUCTURES_H
