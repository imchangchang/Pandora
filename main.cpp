/*
 * main.cpp
 *
 *  Created on: Oct 11, 2020
 *      Author: imcha
 */
#include "beep.hpp"
#include "button.hpp"
#include "led.hpp"
#include "stm32l4xx_hal.h"

Gpio GpioR(GPIOE, GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP,
           GPIO_SPEED_FREQ_LOW);
Gpio GpioG(GPIOE, GPIO_PIN_8, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP,
           GPIO_SPEED_FREQ_LOW);
Gpio GpioB(GPIOE, GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP,
           GPIO_SPEED_FREQ_LOW);

Led LedR(GpioR);
Led LedG(GpioG);
Led LedB(GpioB);

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

LedRgb myRgb(LedR, LedG, LedB);

extern "C" void SystemClock_Config(void);

void update(uint32_t time_ms) {
  Key0.scan(time_ms);
  Key1.scan(time_ms);
  Key2.scan(time_ms);
  KeyWKUP.scan(time_ms);
  myBeep.run(time_ms);
}
int main(void) {
  HAL_Init();
  SystemClock_Config();

  while (1) {
    uint32_t time_ms = HAL_GetTick();
    update(time_ms);

    if (Key0.event_pressed()) {
      myBeep.on(100);
    }
    if (Key1.event_release()) {
      myBeep.on(100);
    }

    if (Key0.pressed()) {
      myRgb.Write(LedColor::BLUE);
    } else if (Key1.pressed()) {
      myRgb.Write(LedColor::RED);
    } else if (Key2.pressed()) {
      myRgb.Write(LedColor::GREEN);
    } else if (KeyWKUP.pressed()) {
      myRgb.Write(LedColor::WHITE);
    } else {
      myRgb.Write(LedColor::OFF);
    }
  }
  return 0;
}
