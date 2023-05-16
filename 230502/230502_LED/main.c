/*
 * 230502_LED.c
 *
 * Created: 2023-05-02 오후 12:01:23
 * Author : USER
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

///* LED 1개 */
//int main(void)
//{
    //DDRA = 0xff;		//DDRx = 입출력 결정
	//while(1)
	//{
		//PORTA = 0x00;	// 포트 D를 전부 0V로
		//_delay_ms(500);
		//PORTA = 0x01;
		//_delay_ms(500); // 포트D의 0번비트만 5V로
	//}
//}




/* LED 8개 */
//int main(void)
//{
	//DDRA = 0xff;        // 포트 방향 출력 설정
	//while(1)
	//{
		//PORTA = 0x00;	// 포트(LED)를 끄는 것
		//_delay_ms(500);
		//PORTA = 0xff;   // 포트(LED)를 키는 것
		//_delay_ms(500); 
	//}
//}



///* LED 4개, 4개 켜보기 */
//int main(void)
//{
//DDRA = 0xFF;     // 포트 방향 출력 설정
//while(1)
//{
//PORTA = 0x0F;	// 포트(LED)를 끄는 것
//_delay_ms(500);
//PORTA = 0xF0;   // 포트(LED)를 키는 것
//_delay_ms(500);
//}
//}

/* 순차적인 LED */
//#define LED_DDRA DDRA
//#define LED_PORTA PORTA
//int main(void)
//{
	//
	//LED_DDRA = 0xff;
	//uint8_t ledData = 0x01;
	//int8_t direction = 1;
	//while (1)
	//{
		//LED_PORTA = ledData;
		//if(direction == 1)
		//{
			//ledData <<= 1;			//비트이동
			//if (ledData == 0x80)	
			//{
				//direction += -1;	// 방향전환
			//}
		//}
		//else if (direction == 0)
		//{
			//ledData >>= 1;
			//if (ledData == 0x01)
			//{
				//direction = 1;
			//}
		//}
		//_delay_ms(300);
	//}
//}

/* 포인터를 이용한 LED 순차 점등*/
#define LED_DDRA DDRA
#define LED_PORTA PORTA

void GPIO_Output(uint8_t data)					//출력 포멧 함수
{
	LED_PORTA = data;
}

void ledInit()									// Dorection 설정(IN/OUT)
{
	LED_DDRA = 0xff;
}

void ledLefttShift(uint8_t *data)				// LED 왼쪽으로 이동
{
	*data = (*data >>7 | (*data << 1));
	GPIO_Output(*data);
}

void ledRighttShift(uint8_t *data)				// LED 오른쪽으로 이동
{
	*data = (*data <<7 | (*data >> 1));
	GPIO_Output(*data);
}

int main(void)
{
	ledInit();
	uint8_t ledData = 0x01;
	while (1)
	{
		for(int i = 0; i<7; i++)
		{
			ledLefttShift(&ledData);
			_delay_ms(500);
		}
		for(int i = 0; i<7; i++)
		{
			ledRighttShift(&ledData);
			_delay_ms(500);
		}
	}
}