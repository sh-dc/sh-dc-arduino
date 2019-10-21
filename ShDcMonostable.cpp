//
// Created by mpapis on 20.07.19.
//

#include "ShDcMonostable.h"

namespace ShDc
{
  Monostable::Monostable(byte pin, void (*init_func)(byte), byte (*read_func)(byte), uint8_t debounce=25)
  {
    m_pin       = pin;
    m_debounce  = debounce;
    m_read_func = read_func;

    init_func(m_pin);

    m_last_time      = get_time();
    m_state.last_pin = m_read_func(m_pin);
    m_state.changed  = 0;
  }

  uint8_t Monostable::type(){
    return SHDC_MONOSTABLE_TYPE;
  }

  void Monostable::read()
  {
    uint32_t time  = get_time();
    byte     value = m_read_func(m_pin);

    if (time - m_last_time > m_debounce && m_state.last_pin != value)
    {
      m_last_time      = time;
      m_state.last_pin = value;
      m_state.changed  = 1;
    }
    else
      m_state.changed = 0;
  }

  uint8_t Monostable::changed(){
    return m_state.changed;
  }

  uint8_t Monostable::state()
  {
    return m_state.last_pin;
  }

  uint32_t Monostable::state_time(){
    return get_time() - m_last_time;
  }

  uint32_t Monostable::get_time(){
    return millis();
  }
}
