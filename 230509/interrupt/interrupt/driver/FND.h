
#ifndef FND_H_
#define FND_H_


#include <avr/io.h>

#define FND_DIGIT_1	0
#define FND_DIGIT_2	1
#define FND_DIGIT_3	2
#define FND_DIGIT_4	3

#define FND_DIGIT_DDR	DDRF
#define FND_DIGIT_PORT	PORTF
#define FND_DATA_DDR	DDRC
#define FND_DATA_PORT	PORTC

void FND_init();
void FND_setFndDisplayData(uint16_t data);	// FND에 표시할 데이터 설정 함수 선언
uint16_t FND_getFndDisplayData();			// FND에 표시된 데이터를 가져오는 함수 선언
void FND_selectDigit(uint8_t digit);		// 표시할 FND 디지트 선택 함수 선언
void FND_showNumber(uint8_t fndNumber);		// 숫자를 표시하는 함수 선언
void FND_off();								// FND 전체를 끄는 함수 선언
void FND_ISR_Display();						// 타이머 인터럽트 발생 시 FND를 표시하는 함수 선언


#endif /* FND_H_ */