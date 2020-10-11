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
    LedState R, G, B;

    HAL_Delay(1000);
    R = LedState::OFF;
    G = LedState::OFF;
    B = LedState::OFF;
    myRgb.Write(R, G, B);

    HAL_Delay(1000);
    R = LedState::ON;
    G = LedState::ON;
    B = LedState::OFF;
    myRgb.Write(R, G, B);

    HAL_Delay(1000);
    R = LedState::OFF;
    G = LedState::ON;
    B = LedState::ON;
    myRgb.Write(R, G, B);

    HAL_Delay(1000);
    R = LedState::ON;
    G = LedState::OFF;
    B = LedState::ON;
    myRgb.Write(R, G, B);

    HAL_Delay(1000);
    R = LedState::ON;
    G = LedState::ON;
    B = LedState::ON;
    myRgb.Write(R, G, B);
  }
  return 0;
}
