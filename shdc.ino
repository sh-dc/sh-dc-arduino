// Smart Home De-Centralised (work in progress)

#include <Arduino.h>
#include <EEPROM.h>
#include <time.h>
#include <JC_Button.h>

/* Rule values:
   0: toggle
   1: toggle, delayed off by `rule_value` seconds of time
   2: turn on, for `rule_value` seconds of time (auto off after `rule_value` seconds of time)
*/
struct TARGETS
{
  // user defined
  const byte     output_pin;
  const uint8_t  rule;
  const uint32_t rule_value;

  // used internally, do not define!
  uint32_t rule_data;
} targets[] =
{
  /*  0 */ {  0, 2, 17 },  // bathroom blinders up   timed 17s (14s measured)
  /*  1 */ {  1, 2, 17 },  // bathroom blinders down timed 17s (14s measured)
  /*  2 */ {  2, 0, 0 },   // bathroom light 1
  /*  3 */ {  3, 0, 0 },   // bathroom light 2
  /*  4 */ {  4, 0, 0 },   // bathroom light 3
  /*  5 */ {  5, 1, 300 }, // bathroom fan +5 min after off
  /*  6 */ {  6, 0, 0 },   // corridor-bedroom light
  /*  7 */ {  7, 0, 0 },   // wc light
  /*  8 */ {  8, 1, 300 }, // wc fan +5min after off
};
const byte targets_count = sizeof(targets) / sizeof(TARGETS);
#define LOOP_TARGETS for (byte target_num = 0; target_num < targets_count; target_num++)
#define TARGET       targets[target_num]

#define BITMASK_CHECK(field, mask)  field & mask
#define BITMASK_SET(field, mask)    field | mask
#define BITMASK_CLEAR(field, mask)  field & ~mask
#define BITMASK_TOGGLE(field, mask) field ^ mask

// bit mask for the SWITCHES flags
#define FLAG_NONE     0
#define FLAG_BISTABLE B1 // monostable otherwise

// bit mask for the SWITCHES state
#define STATE_ENABLED   B001
#define STATE_PROCESSED B010
#define STATE_CHANGED   B100

struct SWITCHES {
  // user defined
  const Button button;
  const byte   flags;

  // used internally, do not define!
  byte state;
} switches[] =
{
  /*  0 */ { Button(A0, 1, 1, 30), FLAG_BISTABLE }, // bathroom blinders up
  /*  1 */ { Button(A1, 1, 1, 30), FLAG_BISTABLE }, // bathroom blinders down
  /*  2 */ { Button(A2, 1, 1, 30), FLAG_NONE },     // bathroom light 1
  /*  3 */ { Button(A3, 1, 1, 30), FLAG_NONE },     // bathroom light 2
  /*  4 */ { Button(A4, 1, 1, 30), FLAG_NONE },     // corridor-bedroom light
  /*  5 */ { Button(A5, 1, 1, 30), FLAG_NONE },     // wc light
};
const byte switches_count = sizeof(switches) / sizeof(SWITCHES);
#define LOOP_SWITCHES for (byte switch_num = 0; switch_num < switches_count; switch_num++)
#define SWITCH        switches[switch_num]

struct CONNECTIONS
{
  // user defined
  const byte source;
  const byte target;
} connections[] =
{
  { 0, 0 }, // bathroom blinders
  { 1, 1 }, // bathroom blinders
  { 2, 2 }, // bathroom light 1
  { 3, 3 }, // bathroom light 2
  { 2, 4 }, // bathroom light 3 on bathroom light 1
  { 3, 4 }, // bathroom light 3 on bathroom light 2
  { 2, 5 }, // bathroom fan on bathroom light 1
  { 3, 5 }, // bathroom fan on bathroom light 2
  { 4, 6 }, // corridor-bedroom light
  { 5, 7 }, // wc light
  { 5, 8 }, // wc fan on wc light
};
const byte connections_count = sizeof(connections) / sizeof(CONNECTIONS);
#define LOOP_CONNECTIONS  for (byte connection_num = 0; connection_num < connections_count; connection_num++)
#define CONNECTION        connections[connection_num]
#define CONNECTION_SWITCH switches[CONNECTION.source]

byte inline load_state(byte switch_num)
{
  return EEPROM.read(switch_num);
}

void inline save_state(byte switch_num, byte state)
{
  EEPROM.update(switch_num, state);
}

void set_target_state(byte target_num, byte state)
{
  switch (TARGET.rule)
  {
    case 0:
      digitalWrite(TARGET.output_pin, state);
      break;
    case 1:
      if (state) {
        TARGET.rule_data = 0;
        digitalWrite(TARGET.output_pin, state);
      } else {
        TARGET.rule_data = time(NULL);
      }
      break;
    case 2:
      if (state) {
        TARGET.rule_data = time(NULL);
        digitalWrite(TARGET.output_pin, state);
      } else {
        TARGET.rule_data = 0;
        digitalWrite(TARGET.output_pin, state);
      }
      break;
  }
}

void check_target_rules(byte target_num)
{
  switch (TARGET.rule)
  {
    case 0: break;
    case 1:
    case 2:
      if (
        digitalRead(TARGET.output_pin) &&
        TARGET.rule_data &&
        time(NULL) - TARGET.rule_data > TARGET.rule_value
      ) {
        TARGET.rule_data = 0;
        digitalWrite(TARGET.output_pin, false);
      }
      break;
  }
}


void setup()
{
  LOOP_TARGETS { pinMode(TARGET.output_pin, OUTPUT); }
  LOOP_SWITCHES {
    SWITCH.button.begin();
    if (load_state(switch_num)) BITMASK_SET(SWITCH.state, STATE_ENABLED | STATE_CHANGED);
  }
}

void inline read_bistable_switch(byte switch_num)
{
  if (
    (SWITCH.button.isPressed() && !BITMASK_CHECK(SWITCH.state, STATE_PROCESSED)) || // first time after press
    (!SWITCH.button.isPressed() && BITMASK_CHECK(SWITCH.state, STATE_PROCESSED))    // first time after leave
  ) {
    BITMASK_SET(SWITCH.state, STATE_CHANGED);
    BITMASK_TOGGLE(SWITCH.state, STATE_PROCESSED);
    BITMASK_TOGGLE(SWITCH.state, STATE_ENABLED);
    save_state(switch_num, BITMASK_CHECK(SWITCH.state, STATE_ENABLED));
  }
}

void inline read_monostable_switch(byte switch_num)
{
  if (SWITCH.button.isPressed())
  {
    if (!BITMASK_CHECK(SWITCH.state, STATE_PROCESSED))
    {
      // first time after press
      BITMASK_SET(SWITCH.state, STATE_CHANGED);
      BITMASK_SET(SWITCH.state, STATE_PROCESSED);
      BITMASK_TOGGLE(SWITCH.state, STATE_ENABLED);
      save_state(switch_num, BITMASK_CHECK(SWITCH.state, STATE_ENABLED));
    }
  } else {
    // first time after leave
    if (BITMASK_CHECK(SWITCH.state, STATE_PROCESSED)) BITMASK_CLEAR(SWITCH.state, STATE_PROCESSED);
  }
}

void inline loop_read_switches()
{
  LOOP_SWITCHES {
    SWITCH.button.read();
    if (BITMASK_CHECK(SWITCH.flags, FLAG_BISTABLE))
      read_bistable_switch(switch_num);
    else
      read_monostable_switch(switch_num);
  }
}

void inline loop_trigger_connections()
{
  LOOP_CONNECTIONS {
    if (BITMASK_CHECK(CONNECTION_SWITCH.state, STATE_CHANGED))
      set_target_state(CONNECTION.target, BITMASK_CHECK(CONNECTION_SWITCH.state, STATE_CHANGED));
  }
}

void inline loop_target_rules()
{
  LOOP_TARGETS { check_target_rules(TARGET.output_pin); }
}

void inline loop_reset_switches_changed()
{
  LOOP_SWITCHES {
    if (BITMASK_CHECK(SWITCH.state, STATE_CHANGED)) BITMASK_CLEAR(SWITCH.state, STATE_CHANGED);
  }
}

void loop()
{
  loop_read_switches();
  loop_trigger_connections();
  loop_target_rules();
  loop_reset_switches_changed();
}
