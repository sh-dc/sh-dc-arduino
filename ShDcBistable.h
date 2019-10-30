//
// Created by mpapis on 20.07.19.
//

#include "ShDcMonostable.h"

#ifndef SHDC_BISTABLE_H
#define SHDC_BISTABLE_H

#define SHDC_BISTABLE_TYPE 2

namespace ShDc
{
  class Bistable : Monostable
  {
   public:
    using Monostable::Monostable;

    uint8_t type();
    void state_handler(Target *target);
  };
}

#endif //SHDC_BISTABLE_H
