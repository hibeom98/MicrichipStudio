#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void UART0_init(void);
void UART0_transmit(char data);	     //UART�� 2���ε� �� �߿��� �츮�� 0���� �� ���� 0�� ���δ�.
unsigned char UART0_receive(void);
volatile uint8_t isIdle;
//�ʱ�ȭ �ϴ� �Լ�                    //������ ��Ʈ 191p
void UART0_init(void)
{
	UBRR0H = 0x00;		            // 2���� 8��Ʈ �������͸� ������ 16��Ʈ ��������, UART0�� ����ϱ� ���� ��������
	UBRR0L = 207;   	     // 2��� ���� ����, �ֳ��ϸ� ������ 9600���� ��ұ� ������
	
	UCSR0A |= (1<<U2X0);  	     //�񵿱�, 8��Ʈ, �и�Ƽ����, 1��Ʈ ���� (stop ��Ʈ�� 1��Ʈ�� �����ش�.), �ø��� ����� ���¸� Ȯ���ϰ� ��� ������ �����ϱ� ���� �������� �� �ϳ�,
	// 2��� ��� ����
	
	//UCSR0C |= 0x06;            // ������ ���� �� ��� ����� �����ϱ� ���� ���
	UCSR0B |= (1<<RXEN0);        // ���ſϷ� ���ͷ�Ʈ �߻��� ���
	UCSR0B |= (1<<TXEN0);        // �۽� �Ϸ� ���ͷ�Ʈ �߻��� ���
}

void UART0_transmit(char data)		// UDRE0 ��Ʈ ���
{
	while ( !(UCSR0A & (1<<UDRE0))); //�۽� ���� ���, �۽� ���۰� ��� �����͸� ���� �غ� �Ǿ� �ִ���
	
	UDR0 = data;   					 //������ ����
	
}
unsigned char UART0_receive(void)
{
	while ( !(UCSR0A & (1<<RXC0)));  // ���ۿ� ���� �ʴ� ���ڰ� ������ 1, ���۰� ��������� 0.
	return UDR0;  					//���������� �����Ϳ� �峪��� ��
	
	
}


int main(void)
{
	DDRA = 0xff;
	PORTA = 0x00;
	uint8_t data;
	
	UART0_init();
	while (1)
	{	
		UART0_transmit(UART0_receive());   //������ ���ÿ� �޴´�
		data = UART0_receive();
		UART0_transmit(data);
		static int led = 0;
		
		
		
		if (data =='a')
		{
			PORTA = 0xff;
		}
		
		if (data == 'b')
		{
			PORTA = 0x00;
		}	
		
		
		if(data == 'c')
		{
			//UDR0 = UART0_receive();
			//if(UDR0 !='c') break;   //������ ���ÿ� �޴´�
			PORTA = (1 << led);
			led++;
			
			if (led == 8)
			{
				led = 0;
			}
			
		}
	}
}
