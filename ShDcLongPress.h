//
// Created by mpapis on 20.07.19.
//

#include "ShDcVirtualSwitch.h"

#ifndef SHDC_LONGPRESS_H
#define SHDC_LONGPRESS_H

#define SHDC_LONGPRESS_TYPE 3

namespace ShDc
{
  class LongPress : VirtualSwitch
  {
   public:
    LongPress(Target *reference_target, vs_time_t delay=1000);
    uint8_t  type();
    void     read();
    uint8_t  changed();
    uint8_t  state();
    uint32_t state_time();
    void     state_handler(Target *target);

   protected:
    struct state_t {
      uint8_t last_value : 1;
      uint8_t changed    : 1;
      uint8_t unused     : 6;
    };

    Target    *m_reference_target;
    state_t   m_state;
    vs_time_t m_delay;
    vs_time_t m_trigger_time;
  };
}

#endif //SHDC_MONOSTABLE_H
