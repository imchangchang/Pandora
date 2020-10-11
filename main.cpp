/*
 * main.cpp
 *
 *  Created on: Oct 11, 2020
 *      Author: imcha
 */
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

LedRgb myRgb(LedR, LedG, LedB);
extern "C" void SystemClock_Config(void);

int main(void) {
  HAL_Init();
  SystemClock_Config();

  while (1) {
    for (uint32_t color = (uint32_t)LedColor::OFF;
         color <= (uint32_t)LedColor::WHITE; color++) {
      HAL_Delay(300);
      myRgb.Write(static_cast<LedColor>(color));
    }
  }
  return 0;
}
