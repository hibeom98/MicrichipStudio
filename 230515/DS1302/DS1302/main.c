#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "DS1302.h"
#include "UART.h"

FILE OUTPUT =FDEV_SETUP_STREAM(UART_transmit, NULL, _FDEV_SETUP_WRITE);

int main(void)
{
	/*
	ds1302 RTC 를 이용하여 시계와 날짜 표시
	*/
   	// uart 초기화
	UART_init();
	stdout = &OUTPUT; // 출력 스트림 지정
	
	// DS1302 초기화
	DS1302_Init();
	
	// RTC에 시간과 날짜를 설정
	DS1302 myTime;	// 구조체 변수 생성
	myTime.year = 23;
	myTime.month = 5;
	myTime.date = 15;
	myTime.dayOfweek = 1;
	myTime.hour = 12;
	myTime.min = 45;
	myTime.sec = 0;
	
	DS1302_SetTimeData(myTime);

    
    while (1) 
    {
		DS1302_GetTime(&myTime);
		DS1302_GetData(&myTime);
		
		printf("20%02d. %02d. %02d. %02d:%02d:%02d\n",
		 myTime.year, myTime.month, myTime.date,
		 myTime.hour, myTime.min, myTime.sec);
		
		_delay_ms(1000);
    }
}

