//
// Created by mpapis on 30.06.19.
//

#ifndef SHDC_STRUCTURES_H
#define SHDC_STRUCTURES_H

struct SWITCHES {
  // user defined
  const ShDc::VirtualSwitch *button;
};

// Rules for targets
#define RULE_ONOFF        0 // toggle
#define RULE_DELLAYED_OFF 1 // toggle, delayed off by `rule_value` seconds of time
#define RULE_TIMER_OFF    2 // turn on for `rule_value` seconds of time, auto off after `rule_value` seconds of time

// Flags for targets
#define FLAG_T_DEFAULT     B0
#define FLAG_T_LOW_TRIGGER B1 // low state trigger relay, otherwise relay is triggered by high state

struct TARGETS
{
  // user defined
  const byte     output_pin;
  const uint8_t  rule;
  const uint32_t rule_value;
  const uint8_t  flags;

  // used internally, do not define!
  uint32_t rule_data;
};

struct CONNECTIONS
{
  // user defined
  const byte source;
  const byte target;
};

#endif //SHDC_STRUCTURES_H
