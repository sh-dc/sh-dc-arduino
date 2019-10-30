//
// Created by mpapis on 30.10.19.
//

#ifndef SHDC_STATE_H
#define SHDC_STATE_H

typedef uint32_t state_time_t;

class State;

struct StateFunctions {
  const void (*init_func)(const State&, const *void);
  const byte (*read_func)(const State&, const *void);
  const void (*write_func)(const State&, const *void);
};

class State {
 public:
  State(const StateFunctions &functions, const void *data);
  void         read();
  byte         changed();
  byte         state();
  state_time_t state_time();
  void         write();

 protected:
  const StateFunctions m_functions;
  const void           *m_data;
  state_time_t         m_last_time;
  byte                 m_state;
  byte                 m_changed;

  state_time_t get_time();
};


#endif //SHDC_STATE_H
