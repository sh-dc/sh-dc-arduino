//
// Created by mpapis on 20.07.19.
//

#include "ShDcLongPress.h"
//#define DEBUG_MODE 300
//#include "debug.h"


namespace ShDc
{
  LongPress::LongPress(Target *reference_target, vs_time_t delay=1000)
  {
    m_reference_target = reference_target;
    m_delay            = delay;
    m_trigger_time     = get_time();
    m_state.last_value = m_reference_target->get_state();
    m_state.changed    = 1;
  }

  uint8_t LongPress::type(){
    return SHDC_LONGPRESS_TYPE;
  }

  void LongPress::read()
  {
    byte value = m_reference_target->get_state();

//    DEBUG_PRINT8("original_value: ", value, " last_pin: ", m_state.last_pin, " original_time: ", m_original_switch->state_time(), " delay: ", m_delay)
    if (value != m_state.last_value)
    {
      m_trigger_time = get_time();
    }
    if (value != m_state.last_value && (!value || get_time() - m_trigger_time > delay ) )
    {
      m_state.changed    = 1;
      m_state.last_value = value;
    }
    else
    {
      m_state.changed = 0;
    }
  }

  uint8_t LongPress::changed(){
    return m_state.changed;
  }

  uint8_t LongPress::state()
  {
    return m_state.last_value;
  }

  vs_time_t LongPress::state_time(){
    return get_time() - m_trigger_time;
  }

  void LongPress::state_handler(Target *target){
    if (changed())
      target->set_state(state());
  }
}
