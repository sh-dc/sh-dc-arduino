//
// Created by mpapis on 30.06.19.
//

#ifndef SHDC_CONFIGURATION_H
#define SHDC_CONFIGURATION_H

#include "sh-dc-arduino/structures.h"

/* Rule values:
   0: toggle
   1: toggle, delayed off by `rule_value` seconds of time
   2: turn on, for `rule_value` seconds of time (auto off after `rule_value` seconds of time)
*/
TARGETS targets[] =
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

SWITCHES switches[] =
{
  /*  0 */ { Button(A0, 1, 1, 30), FLAG_BISTABLE }, // bathroom blinders up
  /*  1 */ { Button(A1, 1, 1, 30), FLAG_BISTABLE }, // bathroom blinders down
  /*  2 */ { Button(A2, 1, 1, 30), FLAG_NONE },     // bathroom light 1
  /*  3 */ { Button(A3, 1, 1, 30), FLAG_NONE },     // bathroom light 2
  /*  4 */ { Button(A4, 1, 1, 30), FLAG_NONE },     // corridor-bedroom light
  /*  5 */ { Button(A5, 1, 1, 30), FLAG_NONE },     // wc light
};

CONNECTIONS connections[] =
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

#endif //SHDC_CONFIGURATION_H
