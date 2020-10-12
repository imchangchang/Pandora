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

extern "C" void SystemClock_Config(void);

static void update(uint32_t time_ms) {
  Key0.scan(time_ms);
  Key1.scan(time_ms);
  Key2.scan(time_ms);
  KeyWKUP.scan(time_ms);
  myBeep.run(time_ms);
}

static void beep_on_key_pressed() {
  constexpr uint32_t BEEP_TIME_MS = 100;
  if (Key0.event_pressed() || Key1.event_pressed() || Key2.event_pressed() ||
      KeyWKUP.event_pressed()) {
    myBeep.on(BEEP_TIME_MS);
  }
}

int main(void) {
  HAL_Init();
  SystemClock_Config();

  while (1) {
    uint32_t time_ms = HAL_GetTick();
    update(time_ms);

    beep_on_key_pressed();

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
