//
// Created by mpapis on 30.06.19.
//

#ifndef SHDC_CONFIGURATION_H
#define SHDC_CONFIGURATION_H

#include "structures.h"

/* Flags
 * FLAG_S_DEFAULT:     just a placeholder for the compiler
 * FLAG_S_BISTABLE: controls if the switch is mono(missing) or bistable(given)
 */
//     id,            1,  2, 3, 4,   5                // 1 -> pin, 2 -> dbTime, 3 -> puEnable, 4 -> invert, 5 -> flags
SWITCHES switches[] =
{
  /*  0 */ { Button(A0, 30, 1, 1), FLAG_S_BISTABLE }, // bathroom blinders up
  /*  1 */ { Button(A1, 30, 1, 1), FLAG_S_BISTABLE }, // bathroom blinders down
  /*  2 */ { Button(A2, 30, 1, 1), FLAG_S_DEFAULT },  // bathroom light 1
  /*  3 */ { Button(A3, 30, 1, 1), FLAG_S_DEFAULT },  // bathroom light 2
  /*  4 */ { Button(A4, 30, 1, 1), FLAG_S_DEFAULT },  // corridor-bedroom light
  /*  5 */ { Button(A5, 30, 1, 1), FLAG_S_DEFAULT },  // wc light
};

/* Rule values:
   RULE_ONOFF:        toggle
   RULE_DELLAYED_OFF: toggle, delayed off by `rule_value` seconds of time
   RULE_TIMER_OFF:    toggle, turn on for `rule_value` seconds of time, auto off after `rule_value` seconds of time

   Flags:
   FLAG_T_DEFAULT
   FLAG_T_LOW_TRIGGER: low state trigger relay, otherwise relay is triggered by high state
*/
//   id,    pin, rule,       rule value, flags
TARGETS targets[] =
{
  /*  0 */ { 11, RULE_TIMER_OFF,    17,  FLAG_T_DEFAULT },     // bathroom blinders up   timed 17s (14s measured)
  /*  1 */ { 10, RULE_TIMER_OFF,    17,  FLAG_T_DEFAULT },     // bathroom blinders down timed 17s (14s measured)
  /*  2 */ {  9, RULE_ONOFF,        0,   FLAG_T_DEFAULT },     // bathroom light 1
  /*  3 */ {  8, RULE_ONOFF,        0,   FLAG_T_DEFAULT },     // bathroom light 2
  /*  4 */ {  7, RULE_ONOFF,        0,   FLAG_T_DEFAULT },     // bathroom light 3
  /*  5 */ {  6, RULE_DELLAYED_OFF, 600, FLAG_T_DEFAULT },     // bathroom fan 10 min after off
  /*  6 */ {  5, RULE_ONOFF,        0,   FLAG_T_DEFAULT },     // corridor-bedroom light
  /*  7 */ {  4, RULE_ONOFF,        0,   FLAG_T_DEFAULT },     // wc light
  /*  8 */ {  3, RULE_DELLAYED_OFF, 600, FLAG_T_LOW_TRIGGER }, // wc fan 10 min after off
};

//  1, 2  // 1 -> source, 2-> target
CONNECTIONS connections[] =
{
  { 0, 0 }, // bathroom blinders
  { 1, 1 }, // bathroom blinders
  { 2, 2 }, // bathroom light 1
  { 2, 4 }, // bathroom light 3 on bathroom light 1
  { 2, 5 }, // bathroom fan on bathroom light 1
  { 3, 4 }, // bathroom light 3 on bathroom light 2
  { 3, 3 }, // bathroom light 2
  { 3, 5 }, // bathroom fan on bathroom light 2
  { 4, 6 }, // corridor-bedroom light
  { 5, 7 }, // wc light
  { 5, 8 }, // wc fan on wc light
};

#endif //SHDC_CONFIGURATION_H
