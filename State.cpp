//
// Created by mpapis on 30.10.19.
//

#include "State.h"

State::State(const StateFunctions &functions, const void &data) {
  m_functions = functions;
  m_data      = data;
  m_last_time = get_time();

  if (m_functions.init_func)
    m_functions.init_func(self, m_data);
}

void State::read() {
  byte new_state = m_functions.read_func(self, m_data);

  if (new_state != m_state) {
    m_state     = new_state;
    m_changed   = 1;
    m_last_time = get_time();
  } else {
    m_changed   = 0;
  }
}

byte State::changed() {
  return m_changed;
}

byte State::state() {
  return m_state;
}

state_time_t State::state_time() {
  return get_time() - m_last_time;
}

void State::write() {
  if (m_functions.write_func)
    m_functions.write_func(self, m_data);
}

state_time_t State::get_time() {
  return millis();
}
