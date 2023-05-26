#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "I2C_LCD.h"
#include "I2C.h"
#include "Button.h"
#include "avr/interrupt.h"
#define C4  262 //261.63HZ
#define D4  294 //293.66HZ
#define E4  330 //329.63HZ
#define F4  349 //349.23HZ
#define G4  392 //392.00HZ
#define A4  440 //440.00HZ
#define B4  494 //493.88HZ
#define C5  523 //523.25HZ
#define PAUSE 0
#define PRESCALER 8

const int melody[]={C4, PAUSE, PRESCALER};
uint8_t buff[30];						// LCD 기판 
int stop;								// PE4번 인터럽트를 체크해주기 위하여 설정

void music_init()
{
	DDRB |= (1<<PORTB6);
	
	TCCR1A |= (1<<COM1B0);				// 비교일치 발생시 출력 반전
	TCCR1B |= (1<<WGM12) | (1<<CS11);
}
 
void music_play(const int *pMusic)
{
	int num;
	
	while (*pMusic)
	{
		num = *pMusic;
		*pMusic++;
		
		if (num == PAUSE)
		{
			OCR1A = 0;					// 재생중지, 듀티사이클 0%
		}
		else
		{
			// 주파수 계산
			int ocr_value = F_CPU / 2 / PRESCALER / num;
			
			// 주파수 설정
			OCR1A = ocr_value;
		}
		_delay_ms(500);
	}
	OCR1A = 0;
}

 

ISR(INT3_vect)								 // pause (인터럽트)
{
	if (PIND & (1 << PIND3))				 // 스위치 2번이 눌린다면
	{
		while(1)
		{
			PORTA &= 0x01;					 // LED가 1개만 켜짐
			sprintf(buff,"pause     ");		 // Pause가 LCD에 표시
			LCD_WriteStringXY(1,9,buff);	 // LCD 위치
			OCR3C = 0;						 // 모터 정지
			if (PIND & (1 << PIND2))		 // 스위치1번이 눌린다면
			{
				sprintf(buff,"run!!");		 // run이 LCD에 표시
				LCD_WriteStringXY(1,9,buff); // LCD 위치 
				PORTA |= 0xff;				 // LED ALL On 
				break;						 // While 문을 빠져나와 멈추었던 시점에서 시작
			}
		}
	}
}


ISR(INT4_vect)								// stop(인터럽트)
{
	stop=1;									// int main 구간에서 인터럽트를 점검해주기 위한 변수
	if (PINE & (1 << PINE4))				// 만약 3번 스위치가 눌린다면
	{						
		while(1)
		{
		LCD_Init();							// LCD 초기화
		PORTA &= 0x00;						// LED ALL OFF
		OCR3C = 0;							// 모터 정지
		sprintf(buff,"stop");				// LCD "STOP"
		LCD_WriteStringXY(1,4,buff);		// LCD 위치
		_delay_ms(2000);					// 2초간 유지
		sprintf(buff,"goodbye");			// LCD "goodbye"
		LCD_WriteStringXY(1,4,buff);		// LCD 위치
		_delay_ms(2000);					// 2초간 유지
		break;								// While 빠져나오기
		}
	}
}

void pwm_init()
{
	// 모드5 : 8비트고속PWM모드 timer 3
	TCCR3A |= (1 << WGM30);
	TCCR3B |= (1 << WGM32);
	
	// 비반전 모드 TOP: 0xff 비교일치값 : OCR3C : PE5
	TCCR3A |= (1 << COM3C1);
	// 분주비 64  16000000/64  ==> 250000HZ(250KHZ)
	// 256 / 250000 ==> 1.02ms
	// 127 / 250000 ==> 0.5ms
	TCCR3B |= ( 1 << CS31)  | (1 << CS30);   // 분주비 64
	// 1600000HZ / 64분주 ==> 250000HZ (250KHZ)
	//
	OCR3C=0;  // PORTE.5
}
// ENA : PORTE.5 (OCR3B(PE5) <=== PORTE.4
// IN1 : PORTE.0
// IN2 : PORTE.2

int main(void)
{	
	 /*버튼에 대한 구조체 변수 선언*/
	 Button buttonOn;
	 Button buttonSpeed;
	 Button buttonStop;
	 uint16_t count = 0;
	 
	 uint8_t i=0;
	  DDRE=0x00;
	  LCD_Init();
	  pwm_init();
	  count=+1;
	  LCD_WriteStringXY(0,0,"1.srt");
	  LCD_WriteStringXY(0,9,"2.pause");
	  LCD_WriteStringXY(1,0,"3.stop");
	  
	  EIMSK |= (1<<INT4) | (1<<INT3);		// 인터럽트
	  EICRB |= (1<<ISC41) | (1<<ISC40);		// 인터럽트
	  EICRA |=(1<<ISC31) | (1<<ISC30);		// 인터럽트
	  sei();								// 인터럽트
	  
	  
	  /*버튼 초기화 함수를 호출하여 버튼 구조체 변수 초기화*/
	  Button_Init(&buttonOn, &BUTTON_DDR, &BUTTON_PIN, BUTTON_ON);			// 버튼1번
	  Button_Init(&buttonSpeed, &BUTTON_DDR, &BUTTON_PIN, BUTTON_SPEED);	// 버튼2번
	  Button_Init(&buttonStop, &BUTTON_DDR, &BUTTON_PIN,BUTTON_STOP);		// 버튼3번
	  
	 
	 
	  DDRE |= ( 1 << 0) | ( 1 << 2) | ( 1 << 5);  // PE.0 PE.2 PE.5 입력 모드로 설정
	  
		
	  
	  // 1) 모터 정지(2초) --> 2) 모터를 정회전(중간속도) 2초 --> 3)모터 정지(2초) --> 4) 모터역회전(중간속도)
	  // 5) 모터역회전(최대속도) : 2초간
	  
	 DDRA |= 0xff;
		
	while(1)
	{
			 LCD_WriteStringXY(0,0,"1.srt");
			 LCD_WriteStringXY(0,9,"2.pause");
			 LCD_WriteStringXY(1,0,"3.stop");
		
		/*세탁 시작 정회전 및 역회전*/
	
		if (PIND & (1 << PIND2))	   //1번 버튼( 풀 다운 저항) --> 세탁기 동작
		{
			PORTA |= 0xff;
			sprintf(buff,"run!!");
			LCD_WriteStringXY(1,9,buff);
		
		
			// 정회전 :  PE2:0,  PE0:1 
			for (uint8_t i=0; i<5; i++)
			{
				PORTE &= 0b11111011;  // 모터정지 : PE0:0 PE2:0
				PORTE |= 0b00000001;  // 정회전   : PE2:0 PE1:1
				OCR3C=127;
				_delay_ms(1000);	  // 1초간 유지
					if(stop)
					{
						break;
					}
		
			// 역회전 : PE2:1,   PE0:0
				PORTE &= 0b11111110;   // 모터정지 : PE0:0 PE2:0
				PORTE |= 0b00000100;   // 역회전
				OCR3C=127;
				_delay_ms(1000);	   // 1초간 유지
		
				if(stop)
				{
					break;
				}
		
			}
			if(stop)				  // 인터럽트 체크
			{
				stop = 0;
				PORTE |= 0b11111111;
				LCD_Init();	
				continue;
			}

			PORTE |= 0b11111111;      // 모터 정지
		
			if(stop)				  // 인터럽트 체크
			{
				stop = 0;
				PORTE |= 0b11111111;
				LCD_Init();	
				continue;
			}
		
			_delay_ms(500);
		
			if(stop)				  // 인터럽트 체크
			{
				stop = 0;
				PORTE |= 0b11111111;
				LCD_Init();	
				continue;
			}
		
		
		
			/*탈수 시작*/
		
			// 정회전 : PE2:0 PE0 1
			sprintf(buff,"run!!");		
			LCD_WriteStringXY(1,9,buff);
			_delay_ms(200);
		
			if(stop)				  // 인터럽트 체크
			{
				stop = 0;
				PORTE |= 0b11111111;
				LCD_Init();	
				continue;
			}
		
		
			for (uint8_t i = 0;i<5;i++)
			{
				PORTE &= 0b11111011;  // 모터정지 : PE0:1 PE2:0
				PORTE |= 0b00000001;
				OCR3C=127;            // 0.5ms 중간속도
				_delay_ms(1000);
			
				if(stop)			  // 인터럽트 체크
				{
					break;
				}
			}
		
			if(stop)				  // 인터럽트 체크
			{
				stop = 0;
				PORTE |= 0b11111111;
				LCD_Init();	
				continue;
			}
		
			sprintf(buff,"run!!");
			LCD_WriteStringXY(1,9,buff);
		
			for (uint8_t i = 0; i<5; i++)		
			{
				PORTE &= 0b11111011;  // 모터정지 : PE0:1 PE2:0
				PORTE |= 0b00000001;
				OCR3C=255;            // max speed
				_delay_ms(1000);
				if(stop)			  // 인터럽트 체크
				{
					break;
				}
			}
			if(stop)				  // 인터럽트 체크
			{
				stop = 0;
				PORTE |= 0b11111111;
				LCD_Init();	
				continue;
			}
		
			/*세탁기 종료*/
			PORTA &= 0x00;			  // LED 소등
			PORTE |= 0b11111111;	  // 모터 정지 
			if(stop)				  // 인터럽트 체크
			{
				stop = 0;
				PORTE |= 0b11111111;
				LCD_Init();	
				continue;
			}
		
			sprintf(buff,"finish   ");
			LCD_WriteStringXY(1,9,buff);
		
			/*끝났다는 부저음 알림*/
			music_init();
			music_play(melody);
			_delay_ms(1);
		
			if(stop)				  // 인터럽트 체크
			{
				stop = 0;
				PORTE |= 0b11111111;
				LCD_Init();	
				continue;
			}
				
			sprintf(buff,"       ");
			LCD_WriteStringXY(1,9,buff);
		
		}	//IF(버튼1번)
	}
}


