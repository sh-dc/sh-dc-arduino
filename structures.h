//
// Created by mpapis on 30.06.19.
//

#ifndef SHDC_STRUCTURES_H
#define SHDC_STRUCTURES_H

#include <Arduino.h>

struct SWITCHES {
  // user defined
  const ShDc::VirtualSwitch *button;
};


struct CONNECTIONS
{
  // user defined
  const byte source;
  const byte target;
};

#endif //SHDC_STRUCTURES_H
