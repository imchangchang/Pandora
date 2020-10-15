/*
 * uart.hpp
 *
 *  Created on: Oct 12, 2020
 *      Author: imcha
 */

#ifndef HAL_UART_HPP_
#define HAL_UART_HPP_

#include <stdarg.h>
#include <stdio.h>

#include "gpio.hpp"

class Uart {
 public:
  Uart()
      : Rx(GPIOA, GPIO_PIN_9, GPIO_MODE_AF_PP, GPIO_PULLUP,
           GPIO_SPEED_FREQ_HIGH, GPIO_AF7_USART1),
        Tx(GPIOA, GPIO_PIN_10, GPIO_MODE_AF_PP, GPIO_PULLUP,
           GPIO_SPEED_FREQ_HIGH, GPIO_AF7_USART1) {
    __HAL_RCC_USART1_CLK_ENABLE();
    // WorkLength 00
    USART1->CR2 = 0x00000000;
    USART1->CR1 = 0x00000000;
    // eable Transmitter and receiver
    USART1->CR1 |= USART_CR1_TE;
    USART1->CR1 |= USART_CR1_RE;
    //
    USART1->BRR = 80000000u / 115200u;

    // KEEP UE at end of uart configuration
    // start uart
    USART1->CR1 |= USART_CR1_UE;
  }
  void Run(uint32_t time_ms) {
    static uint32_t last_time_ms = 0;
    if (time_ms - last_time_ms > 1000) {
      last_time_ms = time_ms;
      // send a byte to pc
    }
  }
  void Send(uint8_t a) {
    while ((USART1->ISR & USART_ISR_TXE) == 0)
      ;
    USART1->TDR = a;
  }
  void print(char *t, ...) {
    char buf[100] = {0};
    va_list st;
    va_start(st, t);
    int len = vsprintf(buf, t, st);
    for (int i = 0; i < len; i++) {
      Send(buf[i]);
    }
    va_end(st);
  }

 private:
  Gpio Rx, Tx;
};

#endif /* HAL_UART_HPP_ */
