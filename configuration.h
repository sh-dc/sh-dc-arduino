//
// Created by mpapis on 30.06.19.
//

#ifndef SHDC_CONFIGURATION_H
#define SHDC_CONFIGURATION_H

Target *light1 = new Target(12, RULE_ONOFF, 0, FLAG_T_DEFAULT);

ShDc::VirtualSwitch *light_switch_1      = (ShDc::VirtualSwitch*)new ShDc::Monostable(A0, &pin_init_input_pullup, &pin_read_invert);
ShDc::VirtualSwitch *light_switch_1_lp_1 = (ShDc::VirtualSwitch*)new ShDc::LongPress (light_1, 1000);
ShDc::VirtualSwitch *light_switch_2      = (ShDc::VirtualSwitch*)new ShDc::Bistable  (A1, &pin_init_input_pullup, &pin_read_invert);

ShDc::VirtualSwitch* switches[] = {
  light_switch_1,
  light_switch_1_lp_1,
  light_switch_2
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
Target targets[] =
{
  /*  0 */ &light1, #TODO: migrate to class!
  /*  1 */ { 11, RULE_ONOFF,          0, FLAG_T_DEFAULT },
  /*  2 */ {  5, RULE_ONOFF,          0, FLAG_T_DEFAULT },
};

//  1, 2  // 1 -> source, 2-> target
CONNECTIONS connections[] =
{
  { 0, 0 },
  { 1, 1 },
  { 2, 2 },
};

#endif //SHDC_CONFIGURATION_H
