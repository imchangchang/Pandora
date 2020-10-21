/*
 * hardware.cpp
 *
 *  Created on: Oct 12, 2020
 *      Author: imcha
 */

#include "hardware.hpp"

Gpio GpioR(GPIOE, GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP,
           GPIO_SPEED_FREQ_LOW);
Gpio GpioG(GPIOE, GPIO_PIN_8, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP,
           GPIO_SPEED_FREQ_LOW);
Gpio GpioB(GPIOE, GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP,
           GPIO_SPEED_FREQ_LOW);
Led LedR(GpioR);
Led LedG(GpioG);
Led LedB(GpioB);
LedRgb myRgb(LedR, LedG, LedB);

Gpio GpioKey0(GPIOD, GPIO_PIN_10, GPIO_MODE_INPUT, GPIO_NOPULL,
              GPIO_SPEED_FREQ_HIGH);
Gpio GpioKey1(GPIOD, GPIO_PIN_9, GPIO_MODE_INPUT, GPIO_NOPULL,
              GPIO_SPEED_FREQ_HIGH);
Gpio GpioKey2(GPIOD, GPIO_PIN_8, GPIO_MODE_INPUT, GPIO_NOPULL,
              GPIO_SPEED_FREQ_HIGH);
Gpio GpioKeyWKUP(GPIOC, GPIO_PIN_13, GPIO_MODE_INPUT, GPIO_NOPULL,
                 GPIO_SPEED_FREQ_HIGH);

Button Key0(GpioKey0);
Button Key1(GpioKey1);
Button Key2(GpioKey2);
Button KeyWKUP(GpioKeyWKUP, GPIO_PIN_SET);

Gpio GpioBeep(GPIOB, GPIO_PIN_2, GPIO_MODE_OUTPUT_PP, GPIO_PULLDOWN,
              GPIO_SPEED_FREQ_LOW);
Beep myBeep(GpioBeep);

Timer timer;
Uart uart1;
