#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "UART.h"

// 출력 스트림 설정<stdio.h>에 있는 표준 입출력
//FILE OUTPUT = FDEV_SETUP_STREAM(UART_transmit, NULL, _FDEV_SETUP_WRITE);


char rxBuff[100] = {0,};
uint8_t rxflag = 0;


ISR(USART0_RX_vect)						 // 수신 1byte가 들어오면 interruot 되도록
{
	static uint8_t rxHead = 0;           // 수신된 데이터의 인덱스
	uint8_t rxData = UDR0;				 // 수신된 데이터
	if (rxData == '\n' || rxData =='\r') // 데이터의 마지막이 개행이나 리턴이면
	{
		rxBuff[rxHead] = '\0';			// 수신된 문자열 마지막에 NULL 추가
		rxHead = 0;						//인덱스 초기화
		rxflag = 1;						// 문자열 수신 플래그 설정
	}
	
	else								// 아니면 계속 다음 문자 받음
	{
		rxBuff[rxHead] = rxData;		// 버퍼에 수신된 데이터 추가
		rxHead++;						// 인덱스 증가
	}
}

int main(void)
{
	DDRA = 0xff;
		
	UART_init();						// 초기화
	uint8_t rxData;
	//stdout = &OUTPUT;
	
	sei();
	
    while (1) 
    {
		
		if (rxflag == 1)				// 문자열 수신이 완료 되면
		{
			rxflag = 0;					//	프래그 초기화
			
			UART_print_string(rxBuff);		
			//printf(rxBuff);			// 수신된 문자열 출력
		}
		
		if (rxflag = 'a')
		{
			DDRA  |= 0xff; 
		}
    }
}

