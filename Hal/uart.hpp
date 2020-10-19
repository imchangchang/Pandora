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
#include <string.h>

#include "gpio.hpp"
template <uint32_t _SIZE>
class RingBuffer {
 public:
  RingBuffer() {
    head = 1;
    tail = 0;
    memset(buf, 0, sizeof(buf));
  }
  void append(uint8_t data) {
    if (!isFull()) {
      buf[head++] = data;
      head %= SIZE;
    }
  }
  uint8_t pop() {
    uint8_t res = 0;
    if (!isEmpty()) {
      res = buf[++tail];
      tail %= SIZE;
    }
    return res;
  }
  bool isEmpty() { return head == (tail + 1) % SIZE; }
  bool isFull() { return (head) % SIZE == tail; }
  uint32_t size() {
    if (isEmpty())
      return _SIZE;
    else if (isFull())
      return 0;
    else {
      if (head > tail)
        return head - tail - 1;
      else
        return tail - head - 1;
    }
  }
  uint8_t operator[](int idx) { return buf[idx]; }
  uint8_t getHead() { return head; }
  uint8_t getTail() { return tail; }

 private:
  static constexpr uint32_t SIZE = _SIZE + 1;
  uint8_t buf[SIZE];
  uint32_t head;
  uint32_t tail;
};

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
  void syncSend(uint8_t a) {
    while ((USART1->ISR & USART_ISR_TXE) == 0)
      ;
    USART1->TDR = a;
  }
  void asyncSend() {
    if ((USART1->ISR & USART_ISR_TXE) != 0) {
      if (!sendbuf.isEmpty()) USART1->TDR = sendbuf.pop();
    }
  }
  void sendhandle() { asyncSend(); }

  void print(char *t, ...) {
    char buf[100] = {0};
    va_list st;
    va_start(st, t);
    int len = vsprintf(buf, t, st);
    for (int i = 0; i < len; i++) {
      sendbuf.append(buf[i]);
    }
    va_end(st);
  }

 private:
  Gpio Rx, Tx;
  RingBuffer<1000> sendbuf;
};

#endif /* HAL_UART_HPP_ */
