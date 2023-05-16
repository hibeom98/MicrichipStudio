/*외부 인터럽트를 사용한 Falling, Rising */
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>



ISR(INT4_vect) // 외부 인터럽트	INT4(PORTE 4번)
{
	PORTA ^= (1<<0);	// LED 연결된 핀, PORTA 0번핀 출력
}

ISR(INT5_vect) // 외부 인터럽트	INT5(PORTE 5번)
{
	PORTA ^= (1<<1);	// LED 연결된 핀, PORTA 1번핀 출력
}



int main(void)
{
    // INT4 Falling Edge일 때 인터럽트 요구 1,0일 때
	EICRB |= (1 << ISC41) | (0 << ISC40);
	
	// INT5 Rising edge 인터럽트 1 ,1 일때
	EICRB |= (1 << ISC51) | (1 << ISC50);
	
	// INT4, INT5 외부인터럽트 활성화 1로 셋팅
	EIMSK |= (1 << INT5) | (1 << INT4);
	
	// 버튼 입력 설정
	DDRE &= ~(1 << DDRE4) | ~(1 << DDRE5);
	
	DDRA = 0xff;
	
	sei();		// 인터럽트 활성화 // cli() << 활성화
	while (1)
	{
		
	}
	
}

