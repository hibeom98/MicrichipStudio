/*
 * LED_2.c
 *
 * Created: 2023-05-03 오전 9:19:54
 * Author : USER
 */ 



#include <avr/io.h>
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define LED_DDR DDRA
#define LED_PORT PORTA




/* 비트 마스킹을 이용한 LED 제어*/
//#define LED_DDR DDRA
//#define LED_PORT PORTA
//
//int main(void)
//{
	//LED_DDR = 0xff;
    //while (1) 
    //{
		//for(uint8_t i = 0 ; i < 4; i++)
		//{
			//LED_PORT = ((0x01 << i) | (0x80 >> i ));
			//_delay_ms(250);
		//}
		//for(uint8_t i = 0 ; i < 4; i++)
		//{
			//LED_PORT = ((0x01 >> i) | (0x80 << i ));
			//_delay_ms(250);
		//}
    //}
//}

/*char를 이용한 LED 제어*/
//#define LED_DDRA DDRA
//int main(void)
//{
	//DDRA = 0xff;
	//unsigned char L = 0x01;
	//unsigned char R = 0x80;
	//while (1)
	//{
		//PORTA = L | R;
		//L <<= 1;
		//if(L==0)
		//{
			//L = 0x01;
		//}
		//
		//R >>= 1;
		//if(R==0)
		//{
			//R = 0x80;
		//}
		//_delay_ms(200);
	//}
//}

/* 배열을 이용한 LED 제어 */
//int main(void)
//{
	//uint8_t ledarr[]={
		//0x81, // 1000 0001
		//0x42, // 0100 0010
		//0x24, // 0010 0100
		//0x18, // 0001 1000
		//0x24, // 0010 0100 
		//0x42, // 0100 0010
		//0x81 // 1000 0001
	//};
	//
	//DDRA = 0xff;
	//while(1)
	//{
			//for (uint8_t i = 0 ; i < 7; i++)
		//{
			//PORTA = ledarr[i];
			//_delay_ms(500);
		//}
	//}
//}



/* 포인터를 이용한 LED 제어 */
//#define LED_DDR DDRA
//#define LED_PORT PORTA
//
//void GPIO_Output(uint8_t data)
//{
	//LED_PORT = data;
//}
//
//void ledInit()
//{
	//LED_DDR = 0xff;	
//}
//
//void leddiagonashift(uint8_t i, uint8_t *data)
//{
	//*data = (1 << i) | (1 << (7-i));
	//
//}
//
//int main()
//{
	//ledInit();
	////uint8_t ledData = 0x81; ==> 1000 0001
	//while(1)
	//{
		//for (uint8_t i = 0; i < 8; i++)
		//{
			//leddiagonashift(i,&ledData);
			//GPIO_Output(ledData);
			//_delay_ms(300);
		//}
	//}
//}


/* xor를 이용한 점등 및 소등 */
//int main ()
//{
	//DDRA =0xFF;
	//uint8_t data = 0x00;
	//while(1)
	//{
		//for(uint8_t i=0; i<8;i++)
		//{
			//data = data ^(1<<(7-i));
			//PORTA =data;
			//_delay_ms(100);
		//}
	//}
//}
//
///* 공간 확보를 통한 LED 점등 및 소등 */
//int main ()
//{
	//DDRA = 0xff;
	//while (1)
	//{
		//for (uint8_t i=0; i<16; i++)
		//{
			//PORTA = 0xff00 >> i;            //그냥 밀어버리는 거다.
			//_delay_ms(200);
		//}
	//}
//}

/* 양쪽으로 갈라지는 LED 점등 */
int main(){
DDRA = 0xff;
while(1)
{
	for (uint8_t i =4; i < 8 ; i++)
	{
		PORTA = 0x01 << i | 0x80 >> i;
		_delay_ms(300);
	}
}
}