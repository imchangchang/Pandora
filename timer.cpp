/*
 * timer.cpp
 *
 *  Created on: Oct 14, 2020
 *      Author: imcha
 */
#include "timer.hpp"

#include "stm32l4xx_hal.h"

void Timer::exec() {
  uint32_t cur_time_ms = HAL_GetTick();
  for (uint8_t i = 0; i < event_size; i++) {
    if (cur_time_ms - event_pool[i].last_run_time_ms > event_pool[i].time_ms) {
      event_pool[i].callback();
      event_pool[i].last_run_time_ms = cur_time_ms;
    }
  }
}

void Timer::add(uint32_t time_ms, void (*callback)(void)) {
  if (event_size < EVENT_POOL_SIZE) {
    uint8_t idx = event_size;
    event_pool[idx].callback = callback;
    event_pool[idx].time_ms = time_ms;
    event_pool[idx].last_run_time_ms = HAL_GetTick();
    event_size++;
  }
}
