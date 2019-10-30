//
// Created by mpapis on 23.07.19.
//

#ifndef SHDC_VIRTUALSWITCH_H
#define SHDC_VIRTUALSWITCH_H

#include <Arduino.h>
#include "ShDcTarget.h"

typedef uint32_t vs_time_t;

namespace ShDc
{
  class VirtualSwitch {
   public:
    virtual uint8_t   type();
    virtual void      read();
    virtual uint8_t   changed();
    virtual uint8_t   state();
    virtual vs_time_t state_time();
    virtual void      state_handler(Target *target);

   protected:
    vs_time_t get_time();
  };
}

#endif //SHDC_VIRTUALSWITCH_H
