/*
 * button.hpp
 *
 *  Created on: Oct 12, 2020
 *      Author: imcha
 */

#ifndef DEVICE_BUTTON_HPP_
#define DEVICE_BUTTON_HPP_

#include "gpio.hpp"
#include "timer.hpp"

class Button {
 public:
  Button(Gpio &gpio, GPIO_PinState press = GPIO_PIN_RESET)
      : _gpio(gpio), _key_pressed(false), press_state(press) {}

  void scan(uint32_t sys_time_ms) {
    if (unstable_stage) {
      if (sys_time_ms > stable_time_ms + 20) {
        if (_key_pressed != is_pressed()) {
          _key_pressed = is_pressed();
        }
        unstable_stage = false;
      }
    } else {
      if (_key_pressed != is_pressed()) {
        unstable_stage = true;
      } else {
        stable_time_ms = sys_time_ms;
      }
    }

    if (_key_pressed_last != _key_pressed) {
      _key_press_event = _key_pressed_last == false;
      _key_release_event = _key_pressed_last == true;
    } else {
      _key_press_event = _key_release_event = false;
    }
    _key_pressed_last = _key_pressed;
  }

  bool pressed() { return _key_pressed; }
  bool event_pressed() { return _key_press_event; }
  bool event_release() { return _key_release_event; }

 private:
  Gpio &_gpio;
  bool _key_pressed;
  bool _key_pressed_last;
  GPIO_PinState press_state;
  uint32_t stable_time_ms = 0;
  bool unstable_stage = false;
  bool _key_press_event;
  bool _key_release_event;
  bool is_pressed() { return _gpio.ReadPin() == press_state; }
};

#endif /* DEVICE_BUTTON_HPP_ */
