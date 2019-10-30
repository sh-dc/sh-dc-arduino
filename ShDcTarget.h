#ifndef SHDC_TARGET_H
#define SHDC_TARGET_H

//TODO: initialize time before we can use it
//#include <time.h>
//TODO: remove when switching to <time.h>
#include <Arduino.h>
uint32_t time(uint32_t param);

// Rules for targets
#define RULE_ONOFF        0 // toggle
#define RULE_DELLAYED_OFF 1 // toggle, delayed off by `rule_value` seconds of time
#define RULE_TIMER_OFF    2 // turn on for `rule_value` seconds of time, auto off after `rule_value` seconds of time

// Flags for targets
#define FLAG_T_DEFAULT     B0
#define FLAG_T_LOW_TRIGGER B1 // low state trigger relay, otherwise relay is triggered by high state

#define BITMASK_CHECK(field, mask)  (field & mask)
#define LOGICAL_XOR(a, b) (!(a) ^ !(b))

class Target
{
 public:
  // user defined
  const byte     output_pin;
  const uint8_t  rule;
  const uint32_t rule_value;
  const uint8_t  flags;

  // used internally, do not define!
  uint32_t rule_data;

  byte get_target_pin()
  {
    return LOGICAL_XOR(digitalRead(output_pin), BITMASK_CHECK(flags, FLAG_T_LOW_TRIGGER));
  }

  void set_target_target_pin(byte state)
  {
    digitalWrite(output_pin, LOGICAL_XOR(state, BITMASK_CHECK(flags, FLAG_T_LOW_TRIGGER)));
  }

  void set_target_state(byte state)
  {
    switch (rule)
    {
      case 0:
        set_target_target_pin(state);
        break;
      case 1:
        if (state) {
          rule_data = 0;
          set_target_target_pin(state);
        } else {
          rule_data = time(NULL);
        }
        break;
      case 2:
        if (state) {
          rule_data = time(NULL);
        } else {
          rule_data = 0;
        }
        set_target_target_pin(state);
        break;
    }
  }

  byte get_state(){
    return get_target_pin();
  }

  void set_state(byte state) {
    set_target_state(state);
  }
};

#endif //SHDC_TARGET_H
