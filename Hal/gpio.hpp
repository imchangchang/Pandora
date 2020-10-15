/*
 * gpio.hpp
 *
 *  Created on: Oct 11, 2020
 *      Author: imcha
 */

#ifndef HAL_GPIO_HPP_
#define HAL_GPIO_HPP_
#include <stdint.h>

#include "stm32l4xx_hal.h"

enum class GpioMode {

};
class Gpio {
 public:
  Gpio(GPIO_TypeDef* GPIOx, uint32_t Pin, uint32_t Mode, uint32_t Pull,
       uint32_t Speed)
      : _GPIOx(GPIOx), _GPIO_Pin(Pin) {
    InitClock(GPIOx);

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = Pin;
    GPIO_InitStruct.Mode = Mode;
    GPIO_InitStruct.Pull = Pull;
    GPIO_InitStruct.Speed = Speed;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
  }
  Gpio(GPIO_TypeDef* GPIOx, uint32_t Pin, uint32_t Mode, uint32_t Pull,
       uint32_t Speed, uint32_t Alternate)
      : _GPIOx(GPIOx), _GPIO_Pin(Pin) {
    InitClock(GPIOx);

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = Pin;
    GPIO_InitStruct.Mode = Mode;
    GPIO_InitStruct.Pull = Pull;
    GPIO_InitStruct.Speed = Speed;
    GPIO_InitStruct.Alternate = Alternate;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
  }
  ~Gpio() { HAL_GPIO_DeInit(_GPIOx, _GPIO_Pin); }
  GPIO_PinState ReadPin() { return HAL_GPIO_ReadPin(_GPIOx, _GPIO_Pin); }
  void WritePin(GPIO_PinState PinState) {
    HAL_GPIO_WritePin(_GPIOx, _GPIO_Pin, PinState);
  }
  void TogglePin() { HAL_GPIO_TogglePin(_GPIOx, _GPIO_Pin); }
  void LockPin() { HAL_GPIO_LockPin(_GPIOx, _GPIO_Pin); }

 private:
  GPIO_TypeDef* _GPIOx;
  uint32_t _GPIO_Pin;
  void InitClock(GPIO_TypeDef* GPIOx) {
    switch ((uint32_t)GPIOx) {
      case (uint32_t)GPIOA_BASE:
        __HAL_RCC_GPIOA_CLK_ENABLE();
        break;
      case (uint32_t)GPIOB_BASE:
        __HAL_RCC_GPIOB_CLK_ENABLE();
        break;
      case (uint32_t)GPIOC_BASE:
        __HAL_RCC_GPIOC_CLK_ENABLE();
        break;
      case (uint32_t)GPIOD_BASE:
        __HAL_RCC_GPIOD_CLK_ENABLE();
        break;
      case (uint32_t)GPIOE_BASE:
        __HAL_RCC_GPIOE_CLK_ENABLE();
        break;
      case (uint32_t)GPIOF_BASE:
        __HAL_RCC_GPIOF_CLK_ENABLE();
        break;
      case (uint32_t)GPIOG_BASE:
        __HAL_RCC_GPIOG_CLK_ENABLE();
        break;
      case (uint32_t)GPIOH_BASE:
        __HAL_RCC_GPIOH_CLK_ENABLE();
        break;
      default:
        break;
    }
  }
};

#endif /* HAL_GPIO_HPP_ */
