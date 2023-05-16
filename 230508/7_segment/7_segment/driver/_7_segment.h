
#ifndef _7_SEGMENT_H_
#define _7_SEGMENT_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define FND_DATA_DDR	 DDRC	// 에 데이터 포트 설정
#define FND_SELECT_DDR	 DDRF	// 샐렉트 포트 설정
#define FND_DATA_PORT	 PORTC	// 데이터 레지스터 설정
#define FND_SELECT_PORT  PORTF	// 셀렉트 레지스터 설정

void FND_Display(uint16_t data);  //디스플레이 함수, 4자리 표현으로 16비트로 설정




#endif /* 7_SEGMENT_H_ */