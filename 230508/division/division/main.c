#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "driver/Button.h"

int main()
{
	LED_DDR = 0xFF;
	
	/*버튼에 대한 구조체 변수 선언*/
	Button buttonOn;
	Button buttonOff;
	Button buttonToggle;
	
	
	/*버튼 초기화 함수를 호출하여 버튼 구조체 변수 초기화*/
	Button_Init(&buttonOn, &BUTTON_DDR, &BUTTON_PIN, BUTTON_ON);
	Button_Init(&buttonOff, &BUTTON_DDR, &BUTTON_PIN, BUTTON_OFF);
	Button_Init(&buttonToggle, &BUTTON_DDR, &BUTTON_PIN,BUTTON_TOGGLE);
	
	while(1)
	{
		if (Button_GetState(&buttonOn)==RELEASED_ACTION)
		{
			LED_PORT = 0xFF;
		}
		if (Button_GetState(&buttonOff)==RELEASED_ACTION)
		{
			LED_PORT = 0x00;
		}
		if (Button_GetState(&buttonToggle)==RELEASED_ACTION)
		{
			LED_PORT ^= 0xFF;
		}
	}
	
}