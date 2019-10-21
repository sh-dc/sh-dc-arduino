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
  /*  0 */ { Button(13, 30, 1, 1), FLAG_S_BISTABLE }, // blinders vestibule up
  /*  1 */ { Button(12, 30, 1, 1), FLAG_S_BISTABLE }, // blinders vestibule down
  /*  2 */ { Button(A0, 30, 1, 1), FLAG_S_DEFAULT },  // light vestibule 1
  /*  3 */ { Button(A1, 30, 1, 1), FLAG_S_DEFAULT },  // light vestibule 2
  /*  4 */ { Button(A2, 30, 1, 1), FLAG_S_DEFAULT },  // light office 1
  /*  5 */ { Button(A3, 30, 1, 1), FLAG_S_DEFAULT },  // light office 2
  /*  6 */ { Button(A4, 30, 1, 1), FLAG_S_BISTABLE }, // blinders office up
  /*  7 */ { Button(A5, 30, 1, 1), FLAG_S_BISTABLE }, // blinders office down
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
  /*  0 */ { 11, RULE_TIMER_OFF, 24, FLAG_T_DEFAULT }, // blinders office up   timed 24s (21s measured)
  /*  1 */ { 10, RULE_TIMER_OFF, 23, FLAG_T_DEFAULT }, // blinders office down timed 23s (20s measured)
  /*  2 */ {  9, RULE_ONOFF,      0, FLAG_T_DEFAULT }, // light office 1
  /*  3 */ {  8, RULE_ONOFF,      0, FLAG_T_DEFAULT }, // light office 2
  /*  4 */ {  7, RULE_ONOFF,      0, FLAG_T_DEFAULT }, // light office 1
  /*  5 */ {  6, RULE_ONOFF,      0, FLAG_T_DEFAULT }, // light office 2
  /*  6 */ {  5, RULE_TIMER_OFF, 24, FLAG_T_DEFAULT }, // blinders office up   timed 24s (21s measured)
  /*  7 */ {  4, RULE_TIMER_OFF, 23, FLAG_T_DEFAULT }, // blinders office down timed 23s (20s measured)
};

//  1, 2  // 1 -> source, 2-> target
CONNECTIONS connections[] =
{
  { 0, 0 }, // blinders vestibule up
  { 1, 1 }, // blinders vestibule down
  { 2, 2 }, // light vestibule 1
  { 3, 3 }, // light vestibule 2
  { 4, 4 }, // light office 1
  { 5, 5 }, // light office 2
  { 6, 6 }, // blinders office up
  { 7, 7 }, // blinders office down
};

#endif //SHDC_CONFIGURATION_H
