//
// Created by mpapis on 23.07.19.
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
  /*  0 */ { Button(A0, 30, 1, 1), FLAG_S_BISTABLE }, // blinders 1 up
  /*  1 */ { Button(A1, 30, 1, 1), FLAG_S_BISTABLE }, // blinders 1 down
  /*  2 */ { Button(A2, 30, 1, 1), FLAG_S_BISTABLE }, // blinders 2 up
  /*  3 */ { Button(A3, 30, 1, 1), FLAG_S_BISTABLE }, // blinders 2 down
  /*  4 */ { Button(A4, 30, 1, 1), FLAG_S_DEFAULT },  // light 1
  /*  5 */ { Button(A5, 30, 1, 1), FLAG_S_DEFAULT },  // light 2
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
  /*  0 */ { 11, RULE_TIMER_OFF,    24,  FLAG_T_DEFAULT }, // blinders 1 up   timed 24s (21s measured)
  /*  1 */ { 10, RULE_TIMER_OFF,    23,  FLAG_T_DEFAULT }, // blinders 1 down timed 23s (20s measured)
  /*  2 */ {  9, RULE_TIMER_OFF,    24,  FLAG_T_DEFAULT }, // blinders 2 up   timed 24s (21s measured)
  /*  3 */ {  8, RULE_TIMER_OFF,    23,  FLAG_T_DEFAULT }, // blinders 2 down timed 23s (20s measured)
  /*  4 */ {  7, RULE_ONOFF,        0,   FLAG_T_DEFAULT }, // light 1
  /*  5 */ {  6, RULE_ONOFF,        0,   FLAG_T_DEFAULT }, // light 2
};

//  1, 2  // 1 -> source, 2-> target
CONNECTIONS connections[] =
{
  { 0, 0 }, // blinders 1 up
  { 1, 1 }, // blinders 1 down
  { 2, 2 }, // blinders 2 up
  { 3, 3 }, // blinders 2 down
  { 4, 4 }, // light 1
  { 5, 5 }, // light 2
};

#endif //SHDC_CONFIGURATION_H
