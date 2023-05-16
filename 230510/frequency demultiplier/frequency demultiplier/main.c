#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
/* 내부 카운터 쓰는 방법 */
int cnt;					// 카운트 값을 저장할 변수

ISR(TIMER0_OVF_vect)		// 타이머 , 카운트 8비트 오버플로우 인터럽트 서비스 루틴
{
	cnt++;
	TCNT0 = 131;			// 2ms 
	if (cnt == 500)			// 500번 째 인터럽트 발생시 LED 출력을 반전 2ms * 500 = 0.5초
	{
		PORTA =  ~PORTA;	// LED
		cnt = 0;			// 
	}
	
}



int main(void)
{
	DDRA = 0xff;
	//PORTA = 0x00;
	PORTA = 0xaa;
	TCCR0 = (1 << CS02) | (1 << CS01) | (0 << CS00);	// 256 분주
	TIMSK = (1 << TOIE0);	// 타이머, 카운트 01 오버플로 인터럽트 활성화
	
	sei();					// 인터럽트 활성화
	
    while (1) 
    {
		
		
		
		
    }
}

