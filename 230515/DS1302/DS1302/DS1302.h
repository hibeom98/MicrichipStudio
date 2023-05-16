


#ifndef DS1302_H_
#define DS1302_H_

#include <avr/io.h>

#define DS1302_CLK_DDR DDRF
#define DS1302_CLK_PORT PORTF
#define DS1302_DATA_DDR DDRF
#define DS1302_DATA_PORT PORTF
#define DS1302_DATA_PIN PINF
#define DS1302_RST_DDR DDRF
#define DS1302_RST_PORT PORTF

#define DS1302_CLK			4
#define DS1302_DAT			5
#define DS1302_RST			6

#define ADDR_SEC		0x80
#define ADDR_MIN		0x82
#define ADDR_HOUR		0x84
#define ADDR_DATE		0x86
#define ADDR_MONTH		0x88
#define ADDR_DAYOWEEK   0x8a
#define ADDR_YEAR		0x8c		

typedef struct _da1302
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t date;
	uint8_t month;
	uint8_t dayOfweek;
	uint8_t year;
}DS1302;

void DS1302_Init();										// RTC 초기화
void DS1302_Selected();									// RTC 선택
void DS1302_Deselected();								// RTC 선택해제
void DS1302_Clock();									// 클락을 생성해서 공급하기 위함이다.
void DS1302_DatabitSet();								// RTC 데이터 비트를 설정
void DS1302_DataBitReset();								// 비트를 해제
void DS1302_Change_Readmode();							// RTC 읽기 모드 변경
void DS1302_Change_WriteMode();							// RTC 쓰기 모드 변경
uint8_t decimal_to_bcd(uint8_t decimal);				// 10진값을 BCD로 변환하는 함수
uint8_t bcd_to_decimal(uint8_t bcd);					// bcd값을 10진 값으로 변환
void DS1302_TxData(uint8_t txData);						// RTC에 데이터 전송
void DS1302_WiteData(uint8_t address, uint8_t data);	// RTC 측정 주소에 데이터를 씀
void DS1302_SetTimeData(DS1302 timedata);				// 시간과 날짜 설정

uint8_t DS1302_RxData();								// 데이터 수신
uint8_t DS1302_ReadData(uint8_t address);				// 특정 주소에서 데이터 읽음
void DS1302_GetTime(DS1302 *timedata);					// 구조체에 들어가있는 시간 가져옴
void DS1302_GetData(DS1302 *timedata);					// 구조체에 들어가있는 날짜 가져옴!!


#endif /* DS1302_H_ */