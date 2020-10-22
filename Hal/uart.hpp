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
      tail = (tail + 1) % SIZE;
      res = buf[tail];
    }
    return res;
  }
  bool isEmpty() { return head == (tail + 1) % SIZE; }
  bool isFull() { return head == tail; }
  uint32_t size() {
    if (isFull()) return _SIZE;
    if (isEmpty()) return 0;
    if (head > tail)
      return head - tail - 1;
    else
      return _SIZE - tail + head;
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
    USART1->CR1 |= USART_CR1_TXEIE;  //
    USART1->CR1 |= USART_CR1_RXNEIE;
    USART1->CR1 |= USART_CR1_UE;

    // enable interrupt, must after staring uart
    HAL_NVIC_SetPriority(USART1_IRQn, 10, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  }
  void Run() {
    while (!recvbuf.isEmpty()) {
      USART1->CR1 &= ~(USART_CR1_TXEIE);
      sendbuf.append(recvbuf.pop());
      USART1->CR1 |= USART_CR1_TXEIE;
    }
  }
  void print(char *t, ...) {
    char buf[100] = {0};
    va_list st;
    va_start(st, t);
    int len = vsprintf(buf, t, st);
    for (int i = 0; i < len; i++) {
      USART1->CR1 &= ~(USART_CR1_TXEIE);
      sendbuf.append(buf[i]);
      USART1->CR1 |= USART_CR1_TXEIE;
    }
    va_end(st);
  }

  void checkReceiver() {
    if ((USART1->ISR & USART_ISR_RXNE) != 0) {
      recvbuf.append((USART1->RDR));
    }
  }

  Gpio Rx, Tx;
  RingBuffer<100> sendbuf;
  RingBuffer<500> recvbuf;
  bool cansend = false;
};

#endif /* HAL_UART_HPP_ */
