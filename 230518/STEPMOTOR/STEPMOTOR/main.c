#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

/* 스텝 모터 */
uint8_t stempData[] = {0x01, 0x02, 0x04, 0x08};
int stepIndex = -1;
	
uint8_t stepForward(void)
{
	stepIndex++;
	if(stepIndex >= 4)
	{
		stepIndex = 0;
	}
	return stempData[stepIndex];
}

uint8_t stepBackward(void)
{
	stepIndex--;
	if(stepIndex < 0)
	{
		stepIndex = 3 ;
	}
	return stempData[stepIndex];
}

int main(void)
{
	DDRE = 0x0f;
   
    while (1) 
    {
		for(int i = 0; i<2048 ; i++)
		{
			PORTE = stepForward();
			_delay_ms(2);
		}
		_delay_ms(500);
		
		for(int i = 0; i < 2048; i++)
		{
			PORTE = stepBackward();
			_delay_ms(2);
		}
		_delay_ms(500);
    }
}

