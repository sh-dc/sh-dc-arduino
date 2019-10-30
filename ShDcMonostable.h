//
// Created by mpapis on 20.07.19.
//

#include "ShDcVirtualSwitch.h"

#ifndef SHDC_MONOSTABLE_H
#define SHDC_MONOSTABLE_H

#define SHDC_MONOSTABLE_TYPE 1

namespace ShDc
{
  class Monostable : VirtualSwitch
  {
   public:
    Monostable(byte pin, void (*init_func)(byte), byte (*read_func)(byte), uint8_t debounce=25);
    uint8_t   type();
    void      read();
    uint8_t   changed();
    uint8_t   state();
    vs_time_t state_time();
    void      state_handler(Target *target);

   protected:
    struct state_t {
      uint8_t last_pin : 1;
      uint8_t changed  : 1;
      uint8_t unused   : 6;
    };

    byte      m_pin;
    uint8_t   m_debounce; // max 255ms should be enough
    vs_time_t m_last_time;
    state_t   m_state;
    byte      (*m_read_func)(byte);
  };
}

#endif //SHDC_MONOSTABLE_H
