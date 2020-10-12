/*
 * beep.hpp
 *
 *  Created on: Oct 12, 2020
 *      Author: imcha
 */

#ifndef DEVICE_BEEP_HPP_
#define DEVICE_BEEP_HPP_
#include "gpio.hpp"

class Beep {
 public:
  Beep(Gpio &gpio) : _gpio(gpio), _on_time_ms(0), _start_time_ms(0) {}
  void on(uint32_t on_time_ms) { _on_time_ms = on_time_ms; }
  void run(uint32_t time_ms) {
    if (_on_time_ms != 0 && _start_time_ms == 0) {
      _start_time_ms = time_ms;
    }

    if (_start_time_ms + _on_time_ms > time_ms) {
      _gpio.WritePin(GPIO_PIN_SET);
    } else {
      _gpio.WritePin(GPIO_PIN_RESET);
      _start_time_ms = 0;
      _on_time_ms = 0;
    }
  }

 private:
  Gpio &_gpio;
  uint32_t _on_time_ms;
  uint32_t _start_time_ms;
};

#endif /* DEVICE_BEEP_HPP_ */
