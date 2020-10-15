/*
 * timer.hpp
 *
 *  Created on: Oct 14, 2020
 *      Author: imcha
 */

#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <stdint.h>

class Timer {
  static constexpr uint8_t EVENT_POOL_SIZE = 200u;
  typedef struct {
    uint32_t time_ms;
    uint32_t last_run_time_ms;
    void (*callback)(void);
  } event_t;

 public:
  void exec();  // call at 1khz
  void add(uint32_t time_ms, void (*callback)(void));

 private:
  event_t event_pool[EVENT_POOL_SIZE];
  uint8_t event_size = 0;
};

#endif /* TIMER_HPP_ */
