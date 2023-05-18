#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdio.h>
#include "UART.h"
#include "I2C_LCD.h"

FILE OUTPUT = FDEV_SETUP_STREAM(UART_transmit,NULL,_FDEV_SETUP_WRITE);

#define PRESCALER 1024 //분주비

void Timer_Init()
{
	TCCR1B |= (1<<CS12) | (1<<CS10);	//1024 분주비
}

uint8_t measure_distance(void)
{
	// 트리거 핀으로 펄스출력
	PORTB &= ~(1<<PORTB1);	// LOW
	_delay_us(1);
	PORTB |= (1<<PORTB1);	// HIGH
	_delay_us(10);
	PORTB &= ~(1<<PORTB1);	// LOW
	
	
	// 에코핀 HIGH될때까지
	TCNT1 = 0;
	while (!(PINB & 0x01))
	{
		if (TCNT1 > 65000)
		{
			return 0;
		}
	}
	
	// LOW 될때까지
	TCNT1 = 0;
	while (PINB & 0x01)
	{
		if (TCNT1 > 65000)
		{
			TCNT1 =0 ;
			break;
		}
	}
	//에코핀 펄스폭을 마이크로 단위로 계산
	double pulse_width = 1000000.0 * TCNT1 * PRESCALER / F_CPU; // 우리의 cpu에 맞춰서 나누어 줘야 한다.!
	
	// 계산된 펄스폭을 cm로 게산(data_sheet 참조)
	return pulse_width/58;
}
int main(void)
{
	
	uint8_t distance;
	uint8_t buff [30];
	stdout = &OUTPUT;
	
	UART_init();	
	LCD_Init();		// LCD 초기화
	DDRB |= 0x02;	// 트리거핀 출력 설정
	DDRB &= 0xfe;	// 에코핀 입력 설정
	
	Timer_Init();
	
    while (1) 
    {
		distance = measure_distance();	// 거리측정
		printf("Distance : %d cm\r\n",distance);
		
		sprintf(buff,"Distance:%04dcm\r\n",distance);
		LCD_WriteStringXY(0,1,buff);
		_delay_ms(200);
    }
}

