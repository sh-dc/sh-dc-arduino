//
// Created by mpapis on 23.07.19.
//

#include <Arduino.h>

#ifndef SHDC_VIRTUALSWITCH_H
#define SHDC_VIRTUALSWITCH_H

namespace ShDc
{
  class VirtualSwitch {
   public:
    virtual uint8_t  type();
    virtual void     read();
    virtual uint8_t  changed();
    virtual uint8_t  state();
    virtual uint32_t state_time();
  };
}

#endif //SHDC_VIRTUALSWITCH_H
