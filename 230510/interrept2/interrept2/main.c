
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

/*인터럽트를 사용하여 LED 한칸씩 이동하기*/

uint8_t ledshiht = 0xFE;

ISR(INT4_vect)
{
	// 이전 LED 상태에서 한칸씩 이동
	ledshiht = ledshiht << 1;
	
	// 현재 LED 상태에서 오른쪽에 있는 비트(0번 비트)에 1 삽입
	ledshiht = ledshiht | 0x01;
	
	/*ledshiht = ledshiht << 1 | 0x01;  --> 위의 두개를 합쳐놓은 상태 */ 
	
	// ledshift가 1111 1110 일때 다음 1111 1111 되면 1111 1110 초기화
	if (ledshiht == 0xff)
	{
		ledshiht = 0xfe;
	}
	
	// 현재 LED 상태를 포트에 출력
	
	PORTA = ledshiht;
}


int main(void)
{
	PORTA = ledshiht; // 초기값 --> 0xfe
	
	EICRB |= (1 << ISC41) | (0                                                                                                                     << ISC40); 	// 외부 인터럽트 4번 Falling edge 일때
	
	EIMSK |= (1 <<INT4);					// 외부 인터럽트 4번 INT4 허용
	
	DDRA = 0xff;
	
	// 포트4번 입력 설정
	DDRE &= ~(1 << DDRE4);
	
	sei();
    while (1) 
    {
    }
}



/* 채터링 문제 해결  */
volatile uint8_t ledshift = 0xFE;
volatile uint8_t button_pressed = 0;

// 외부 인터럽트 INT4(PORTE 4 번) ISR 정의
ISR(INT4_vect)
{
	button_pressed = 1;
}

int main(void)
{
	DDRA = 0xff;
	DDRE &= ~(1<<DDRE4);
	PORTA = ledshift;
	EICRB |= (1 << ISC41) | (0 << ISC40);
	EIMSK |= (1 <<INT4);	
	sei();
		
	
	while (1)
	{	
		if (button_pressed)
		{
			_delay_ms(50);
			if (!(PINE & ( 1 <<PINE4)))
			{
				ledshift = (ledshift <<1 ) | 0x01;
				if(ledshift == 0xff)
				{
					ledshift = 0xfe;
				}
				PORTA = ledshift;
			}
			button_pressed = 0;
		}
	}
}