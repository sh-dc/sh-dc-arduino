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
//#define DEBUG_MODE 50

#include <Arduino.h>

uint8_t volatile loading = 1;

#include <EEPROM.h>

#include "ShDcTarget.h"
#include "ShDcMonostable.h"
#include "ShDcBistable.h"
#include "ShDcLongPress.h"
#include "PinFunc.h"

#include "debug.h"
#include "structures.h"
#include "configuration.h"

const byte targets_count = sizeof(targets) / sizeof(Target);
#define LOOP_TARGETS for (byte target_num = 0; target_num < targets_count; target_num++)
#define TARGET       targets[target_num]

const byte switches_count = sizeof(switches) / sizeof(SWITCHES);
#define LOOP_SWITCHES for (byte switch_num = 0; switch_num < switches_count; switch_num++)
#define SWITCH        switches[switch_num]

const byte connections_count = sizeof(connections) / sizeof(CONNECTIONS);
#define LOOP_CONNECTIONS  for (byte connection_num = 0; connection_num < connections_count; connection_num++)
#define CONNECTION        connections[connection_num]
#define CONNECTION_SWITCH switches[CONNECTION.source]
#define CONNECTION_TARGET targets[CONNECTION.target]

byte load_state(byte switch_num)
{
  return EEPROM.read(switch_num);
}

void save_state(byte switch_num, byte state)
{
  EEPROM.update(switch_num, state);
}

void check_target_rules(byte target_num)
{
  switch (TARGET.rule)
  {
    case 0: break;
    case 1:
    case 2:
      if (
        TARGET.get_target_pin() &&
        TARGET.rule_data &&
        time(NULL) - TARGET.rule_data > TARGET.rule_value
      ) {
        TARGET.rule_data = 0;
        TARGET.set_target_target_pin(false);
      }
      break;
  }
}

void setup()
{
  DEBUG_INIT("booting!")

  LOOP_TARGETS {
    pinMode(TARGET.output_pin, OUTPUT);
    TARGET.set_target_target_pin(false);
  }

  DEBUG_PRINT1("booted!")
  loading = 0;
}

void loop()
{
  if (loading) return;
  LOOP_SWITCHES
    SWITCH->read();

  LOOP_CONNECTIONS
    CONNECTION_SWITCH->state_handler(&CONNECTION_TARGET);

  LOOP_TARGETS {
    save_state(target_num, TARGET.get_target_pin());
    check_target_rules(target_num);
  }

  #ifdef DEBUG_MODE
    delay(DEBUG_MODE);
  #endif
}
