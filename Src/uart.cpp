/*
 * uart.cpp
 *
 *  Created on: Oct 20, 2020
 *      Author: imcha
 */
#include "uart.hpp"

extern Uart uart1;

extern "C" void USART1_IRQHandler(void) {
  if (((USART1->ISR & USART_ISR_TXE) != 0) &&
      ((USART1->CR1 & USART_CR1_TXEIE) != 0)) {
    if (uart1.sendbuf.isEmpty()) {
      USART1->CR1 &= ~(USART_CR1_TXEIE);
    } else {
      USART1->TDR = uart1.sendbuf.pop();
    }
  }
  if (((USART1->ISR & USART_ISR_RXNE) != 0) &&
      ((USART1->ISR & USART_CR1_RXNEIE) != 0)) {
    uart1.recvbuf.append((USART1->RDR));
  }
}
