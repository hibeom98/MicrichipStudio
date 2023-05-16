#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>	// 인터럽트를 사용하기 위한 인클루드 함수
#include "driver/FND.h"


uint16_t counter = 0;
volatile int cnt;
uint8_t stop;


ISR(TIMER0_OVF_vect) // Interrut Service Routine, 현재의 cs값에서 1.024ms 간격으로 실행
{
	
	cnt++;
	if (cnt==100)							// cnd 시간을 측정하기 위한 변수
	{
		FND_setFndDisplayData(counter++);	// FND에 표시할 함수
		cnt = 0;
	}
	
	
}

ISR(INT4_vect) // 외부 인터럽트	INT4(PORTE 4번)
{
	stop= ~stop;

}

ISR(INT5_vect) // 외부 인터럽트	INT5(PORTE 5번)
{
	counter = 0;
	FND_setFndDisplayData(0);
	stop= ~stop;
}





int main(void)
{
	 // INT4 Falling Edge일 때 인터럽트 요구 1,0일 때
	 EICRB |= (1 << ISC41) | (0 << ISC40);
	 
	 // INT5 Falling edge 인터럽트 1 ,0 일때
	 EICRB |= (1 << ISC51) | (0 << ISC50);
	 
	 // INT4, INT5 외부인터럽트 활성화 1로 셋팅
	 EIMSK |= (1 << INT5) | (1 << INT4);
	 
	 //// 버튼 입력 설정
	 //DDRE &= ~(1 << DDRE4) | ~(1 << DDRE5);		
	
		
	FND_init();
	
	sei();						// 글로벌 인터럽트 인에이블 // 디스에이블 cli()
	
	
    while (1) 
    {
		
		if(stop)
		{
			TCCR0 &= ~((1 << CS02) |(1 << CS01) |(1 << CS00));
		}
		else
		{
			TCCR0 |= (1 << CS02) |(0 << CS01) |(0 << CS00);
		}
		
		
		FND_ISR_Display();		// 타이머 인터럽트 발생 시 FND 를 표시하는 함수
    }
}

