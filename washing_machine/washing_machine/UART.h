
#include <avr/io.h>

#ifndef UART_H_
#define UART_H_

#define FALSE 0
#define TRUE 1

void UART_init(void);
void UART_transmit(char data);
unsigned char UART_receive();
void UART_print_string(char *str);

#endif /* UART_H_ */