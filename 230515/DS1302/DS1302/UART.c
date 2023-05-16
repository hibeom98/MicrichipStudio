# include "UART.h"

void UART_init(void)
{
	UBRR0H = 0x00;
	UBRR0L = 0xCF;					 //207;

	UCSR0A |= (1<<U2X0);			 //비동기, 8비트, 패리티없음, 1비트 정지 (stop 비트는 1비트로 보내준다.), 시리얼 통신의 상태를 확인하고 통신 과정을 제어하기 위한 레지스터 중 하나,
									 // 2배속 모드 설정

									 //UCSR0C |= 0x06;
	UCSR0B |= (1<<RXEN0);			 //RX Complete Interrupt Enable
	UCSR0B |= (1<<TXEN0);			 //TX Complete Interrupt Enable
	
	UCSR0B |= (1 << RXCIE0);
}

void UART_transmit(char data)
{
	while ( !(UCSR0A & (1<<UDRE0))); //WHILE문 안의 (UCSR0A &(1<<UDRE0)이 0이면 무한루프,
									 // 안비어있으면 무한루트이다가 비어있으면 나가서 UDR0=data
									 
	UDR0 = data;					 // UDR0에 데이터가 들어가면 바로 출력
}

unsigned char UART_receive(void)
{
	while ( !(UCSR0A & (1<<RXC0))); 
	//안에값이 0일때 무한루프 0= UDR0에 데이터가
	//아직 다 안들어왔다는뜻			  
}

void UART_print_string(char *str)
{
	for (int i = 0 ; str [i]; i++)
	{	
		UART_transmit(str[i]);		//문자열로 입력할 수있도록 선언
	}
}