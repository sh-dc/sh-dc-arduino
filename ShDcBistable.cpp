//
// Created by mpapis on 20.07.19.
//

#include "ShDcBistable.h"

namespace ShDc
{
  uint8_t Bistable::type(){
    return SHDC_BISTABLE_TYPE;
  }

  void Bistable::state_handler(Target *target){
    if (changed())
      target->set_state(state());
  }
}
