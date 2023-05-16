#include "FND.h"
#include <util/delay.h>
uint16_t fndDisplayData = 0;

void FND_init()
{
	
	TCCR0 |= (1 << CS02) |(0 << CS01) |(0 << CS00); // 타이머, 카운트 동작설정, 1/64 분주비
	TCNT0 = 6;
	TIMSK |= (1 << TOIE0); //Timer/Counter Overflow Interrupt Enable
	FND_DIGIT_DDR |= (1<< FND_DIGIT_1) | (1<<FND_DIGIT_2) | (1<<FND_DIGIT_3) |( 1<< FND_DIGIT_4); // FND 디지트핀을 출력으로 설정
	FND_DATA_DDR = 0xff;	// 데이터핀 출력 설정
	
}

void FND_setFndDisplayData(uint16_t data)
{
	if(data >= 10000)// 7세그먼트 디스플레이는 0~9999까지의 정수만 표시 가능
		data = 9999;
	fndDisplayData = data;	// 데이터 저장
}

uint16_t FND_getFndDisplayData()
{
	return fndDisplayData;  // 저장된 데이터 변환
}

void FND_selectDigit(uint8_t digit)
{
	FND_DIGIT_PORT |= 0xf0;			// 모든 자리수 선택 핀을 HIGH로 설정하여 꺼준다
	FND_DIGIT_PORT =~( 1 << digit);	// 선택한 자릿수 선택 핀을 LOW로 설정하여 켜준다
}

void FND_showNumber(uint8_t fndNumber)
{
	uint8_t fndFont[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};
	FND_DATA_PORT = fndFont[fndNumber];	// 선택한 숫자에 해당하는 7세그먼트 패턴을 데이터 핀에 출력
}

void FND_off()
{
	FND_DIGIT_PORT |= 0xf0; // 모든 자릿수 선택 핀을 HIGH로 설정하여 껴준다.
}

void FND_ISR_Display()
{
	static uint8_t fndDigitPosition = 0;	// 현재 출력중인 자리
	uint16_t displayData = FND_getFndDisplayData();


	fndDigitPosition  = (fndDigitPosition+1)% 4;
	FND_off();

switch (fndDigitPosition)
{
	case 0:
	FND_showNumber(displayData / 1000%10);   //1의 자리 숫자 출력
	FND_selectDigit(FND_DIGIT_4);		// 1의 자리 디지트 선택
	break;
	case 1:
	FND_showNumber(displayData / 100 % 10); //10의 자리
	FND_selectDigit(FND_DIGIT_3);
	break;
	case 2:
	FND_showNumber(displayData / 10%10); //100의 자리
	FND_selectDigit(FND_DIGIT_2);
	break;
	case 3:
	FND_showNumber(displayData %10); //1000의 자리
	FND_selectDigit(FND_DIGIT_1);
	break;
	
}
	_delay_ms(10);
}