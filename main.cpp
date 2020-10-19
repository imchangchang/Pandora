/*
 * main.cpp
 *
 *  Created on: Oct 11, 2020
 *      Author: imcha
 */
#include "hardware.hpp"
#include "stm32l4xx_hal.h"
#include "timer.hpp"
#include "uart.hpp"

extern "C" void SystemClock_Config(void);
Timer timer;
Uart uart1;
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
    uart1.print((char*)"Hello CGeng\r\n");
  }
}

int main(void) {
  RingBuffer<20> testBuffer;
  HAL_Init();
  SystemClock_Config();

  while (1) {
    timer.exec();
    uint32_t time_ms = HAL_GetTick();
    update(time_ms);
    uart1.Run();

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
