/*
 * Smart Home De-Centralised (work in progress)
 */

/* Debugging examples:
 *   DEBUG_PRINT("just a msg")
 *   DEBUG_PRINT2(switch_num, " switch_state: on")
 *   DEBUG_PRINT3(switch_num, " init_switch_state: ", SWITCH.state)
 *
 * Used for debugging, delays loop for readability, comment out for final compilation
 */
//#define DEBUG_MODE 300

#include <stdint.h>

uint8_t volatile loading = 1;

#include <Arduino.h>
#include <EEPROM.h>
//TODO: initialize time before we can use it
//#include <time.h>
//TODO: remove when switching to <time.h>
uint32_t time(uint32_t param) { return millis() / 1000; }

#include "ShDcMonostable.h"
#include "ShDcBistable.h"
#include "PinFunc.h"

#include "debug.h"
#include "structures.h"
#include "configuration.h"

#define BITMASK_CHECK(field, mask)  (field & mask)
#define LOGICAL_XOR(a, b) (!(a) ^ !(b))

const byte targets_count = sizeof(targets) / sizeof(TARGETS);
#define LOOP_TARGETS for (byte target_num = 0; target_num < targets_count; target_num++)
#define TARGET       targets[target_num]

const byte switches_count = sizeof(switches) / sizeof(SWITCHES);
#define LOOP_SWITCHES for (byte switch_num = 0; switch_num < switches_count; switch_num++)
#define SWITCH        switches[switch_num]

const byte connections_count = sizeof(connections) / sizeof(CONNECTIONS);
#define LOOP_CONNECTIONS  for (byte connection_num = 0; connection_num < connections_count; connection_num++)
#define CONNECTION        connections[connection_num]
#define CONNECTION_SWITCH switches[CONNECTION.source]

byte load_state(byte switch_num)
{
  return EEPROM.read(switch_num);
}

void save_state(byte switch_num, byte state)
{
  EEPROM.update(switch_num, state);
}

void set_target_target_pin(byte target_num, byte state)
{
  digitalWrite(TARGET.output_pin, LOGICAL_XOR(state, BITMASK_CHECK(TARGET.flags, FLAG_T_LOW_TRIGGER)));
}

byte get_target_pin(byte target_num)
{
  return LOGICAL_XOR(digitalRead(TARGET.output_pin), BITMASK_CHECK(TARGET.flags, FLAG_T_LOW_TRIGGER));
}

void set_target_state(byte target_num, byte state)
{
  switch (TARGET.rule)
  {
    case 0:
      set_target_target_pin(target_num, state);
      break;
    case 1:
      if (state) {
        TARGET.rule_data = 0;
        set_target_target_pin(target_num, state);
      } else {
        TARGET.rule_data = time(NULL);
      }
      break;
    case 2:
      if (state) {
        TARGET.rule_data = time(NULL);
      } else {
        TARGET.rule_data = 0;
      }
      set_target_target_pin(target_num, state);
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
        get_target_pin(target_num) &&
        TARGET.rule_data &&
        time(NULL) - TARGET.rule_data > TARGET.rule_value
      ) {
        TARGET.rule_data = 0;
        set_target_target_pin(target_num, false);
      }
      break;
  }
}

void setup()
{
  DEBUG_INIT("booting!")

  LOOP_TARGETS {
    pinMode(TARGET.output_pin, OUTPUT);
    set_target_target_pin(target_num, false);
  }

  DEBUG_PRINT1("booted!")
  loading = 0;
}

void loop()
{
  if (loading) return;
  LOOP_SWITCHES
    SWITCH->read();

  LOOP_CONNECTIONS {
    if (CONNECTION_SWITCH->changed()) {
      if (CONNECTION_SWITCH->type() == SHDC_MONOSTABLE_TYPE && CONNECTION_SWITCH->state()) {
        set_target_state(CONNECTION.target, !get_target_pin(CONNECTION.target));
      }
      if (CONNECTION_SWITCH->type() == SHDC_BISTABLE_TYPE) {
        set_target_state(CONNECTION.target, CONNECTION_SWITCH->state());
      }
    }
  }
  LOOP_TARGETS {
    save_state(target_num, get_target_pin(target_num));
    check_target_rules(target_num);
  }

  #ifdef DEBUG_MODE
    delay(DEBUG_MODE);
  #endif
}
