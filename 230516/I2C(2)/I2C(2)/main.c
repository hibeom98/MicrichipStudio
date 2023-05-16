#include <avr/interrupt.h>
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "I2C_LCD.h"
#include "DS1302.h"
#include "UART.h"
#include <stdio.h>

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
	myTime.date = 16;
	myTime.dayOfweek = 1;
	myTime.hour = 14;
	myTime.min = 28;
	myTime.sec = 0;
	
	DS1302_SetTimeData(myTime);
	
	uint16_t count = 0;
	uint8_t buff[30];
	
	
   LCD_Init();
   LCD_WriteStringXY(0,0,"DATE:");
   LCD_WriteStringXY(1,0,"TIME:");
   
    while (1) 
    {
		
		
		DS1302_GetTime(&myTime);
		DS1302_GetData(&myTime);
		
		sprintf(buff,"20%2d.%02d.%02d.", myTime.year, myTime.month, myTime.date); 
		LCD_WriteStringXY(0,5,buff);
		
		sprintf(buff,"%02d:%02d:%02d", myTime.hour, myTime.min, myTime.sec);
		LCD_WriteStringXY(1,5,buff);
		
		_delay_ms(1000);
		
		//sprintf(buff,"count %-5d",count++);
		//LCD_WriteStringXY(1,0,buff);
		//_delay_ms(200);
    }
}

