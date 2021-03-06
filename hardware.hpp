/*
 * hardware.hpp
 *
 *  Created on: Oct 12, 2020
 *      Author: imcha
 */

#ifndef HARDWARE_HPP_
#define HARDWARE_HPP_
#include "beep.hpp"
#include "button.hpp"
#include "led.hpp"
#include "timer.hpp"
#include "uart.hpp"

extern LedRgb myRgb;
extern Button Key0;
extern Button Key1;
extern Button Key2;
extern Button KeyWKUP;
extern Beep myBeep;
extern Timer timer;
extern Uart uart1;

#endif /* HARDWARE_HPP_ */
