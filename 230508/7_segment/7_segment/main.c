#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "driver/7_segment.h"

///* 2가 켜지는 코드 */
//int main(void)
//
//{
	//DDRC = 0xff;
	//PORTC = 0x5B;
//
    //while (1) 
    //{
		//PORTC = 0x5B;
		//_delay_ms(500);
    //}
//}


/* FND 숫자 증가 */
//int main(void)
//
//{
	//uint8_t FND_Number[]
	//={0x3f, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};
		//
		//int count = 0;
		//DDRC = 0xff;
		//
		//while (1)
		//{
			//PORTC = FND_Number[count];
			//count = (count + 1) % 10;
			//_delay_ms(500);
		//}
//}


/* 순차적인 FND 증가 */
int main(void)
{
	FND_DATA_DDR = 0xff;
	FND_SELECT_DDR = 0xff;
	FND_SELECT_PORT = 0x00;
	uint16_t count = 0;
	uint32_t timeTick = 0; 
	uint32_t prevTime = 0;
	
	while(1)
	{
		FND_Display(count);
		if (timeTick - prevTime > 100)			 //100ms가 지날때마다 count 값 1씩 증가
		{
			prevTime = timeTick;
			count++;
		}
		_delay_ms(1);							// 1ms 지연시간
		timeTick++;								// 시간을 1ms 씩 증가
	}
}




