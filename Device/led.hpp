/*
 * led.hpp
 *
 *  Created on: Oct 11, 2020
 *      Author: imcha
 */

#ifndef DEVICE_LED_HPP_
#define DEVICE_LED_HPP_
#include "gpio.hpp"
enum class LedState { OFF = 0, ON };
class Led {
 public:
  Led(Gpio &gpio) : _gpio(gpio) { _gpio.WritePin(GPIO_PIN_SET); }
  void Write(LedState state) {
    if (state == LedState::ON)
      _gpio.WritePin(GPIO_PIN_RESET);
    else
      _gpio.WritePin(GPIO_PIN_SET);
  }
  void Toggle(void) { _gpio.TogglePin(); }

 private:
  Gpio &_gpio;
};

class LedRgb {
 public:
  LedRgb(Led &R, Led &G, Led &B) : _R(R), _G(G), _B(B) {}
  void Write(LedState R, LedState G, LedState B) {
    _R.Write(R);
    _G.Write(G);
    _B.Write(B);
  }

 private:
  Led &_R;
  Led &_G;
  Led &_B;
};

#endif /* DEVICE_LED_HPP_ */
