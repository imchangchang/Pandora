/*
 * main.cpp
 *
 *  Created on: Oct 11, 2020
 *      Author: imcha
 */
#include "flash.hpp"
#include "hardware.hpp"
#include "stm32l4xx_hal.h"

extern "C" void SystemClock_Config(void);
static void update(uint32_t time_ms) {
  Key0.scan(time_ms);
  Key1.scan(time_ms);
  Key2.scan(time_ms);
  KeyWKUP.scan(time_ms);
  myBeep.run(time_ms);
}
Flash flash;

static void beep_on_key_pressed() {
  constexpr uint32_t BEEP_TIME_MS = 100;
  if (Key0.event_pressed() || Key1.event_pressed() || Key2.event_pressed() ||
      KeyWKUP.event_pressed()) {
    myBeep.on(BEEP_TIME_MS);
    uart1.print((char*)"Hello CGeng\r\n");
  }
}

uint64_t data[32];
int main(void) {
  HAL_Init();
  SystemClock_Config();
  for (uint8_t i = 0; i < 32; i++) {
    data[i] = i;
  }

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
    if (Key0.event_pressed()) {
      flash.Read(10);
    }
    if (Key1.event_pressed()) {
      flash.Write(0, 1u << 32 | 2u);
    }
    if (Key2.event_pressed()) {
      flash.WriteRow(0, (uint32_t)data);
    }
    if (KeyWKUP.event_pressed()) {
      flash.Erase();
    }
  }
  return 0;
}
