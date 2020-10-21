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
  USART1->ICR =
      (USART_ICR_PECF | USART_ICR_FECF | USART_ICR_NECF | USART_ICR_ORECF |
       USART_ICR_IDLECF | USART_ICR_TCCF | USART_ICR_LBDCF | USART_ICR_CTSCF |
       USART_ICR_RTOCF | USART_ICR_EOBCF | USART_ICR_CMCF | USART_ICR_WUCF);
}
