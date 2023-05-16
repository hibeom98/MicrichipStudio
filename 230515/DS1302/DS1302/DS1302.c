
#include "DS1302.h"

void DS1302_Init()
{
	/* 클럭핀, 데이터 핀 출력으로 설정
	    리셋핀 LOW 로 설정          */
	DS1302_CLK_DDR  |= (1<<DS1302_CLK);
	DS1302_DATA_DDR |= (1<<DS1302_DAT);
	DS1302_RST_DDR  |= (1<<DS1302_RST);
	
	DS1302_CLK_PORT  &= ~(1<<DS1302_CLK);	// 클락을 초기값 LOW
	DS1302_DATA_PORT |=  (1<<DS1302_DAT);
	DS1302_RST_PORT  &= ~(1<<DS1302_RST);	// 리셋의 초기값 LOW
	
	
}

void DS1302_Selected()
{
	DS1302_RST_PORT |= (1<<DS1302_RST);     // 리셋핀을 HIGH로 설정 (읽거나 쓰거나 둘 중 하나를 하기 위한 준비과정)
}

void DS1302_Deselected()
{
	DS1302_RST_PORT  &= ~(1<<DS1302_RST);	// 리셋의 초기값 LOW
}

void DS1302_Clock()
{
	DS1302_CLK_PORT |= (1<<DS1302_CLK);		// 클럭핀 HIGH
	DS1302_CLK_PORT &= ~(1<<DS1302_CLK);	// 클럭핀 LOW
}

void DS1302_DatabitSet()
{
	DS1302_DATA_PORT |= (1<<DS1302_DAT);	// 데이터핀을 HIGH
}

void DS1302_DataBitReset()
{
	DS1302_DATA_PORT &= ~(1<<DS1302_DAT);
}

void DS1302_Change_Readmode()
{
	DS1302_DATA_DDR &= ~(1<<DS1302_DAT);
}

void DS1302_Change_WriteMode()
{
	DS1302_DATA_DDR |=  (1<<DS1302_DAT);	// 쓰기모드에서 데이터 핀 출력 설정 변경
}

uint8_t decimal_to_bcd(uint8_t decimal)	// 10진 TO BCD
{
	// 변수값이 5 < -- 상위 4비트 자지로  9<-- 하위 4비트에
	// 4비트씩 묶어서 1의자리, 10의자리 저장 리턴
	
	return ((decimal/10)<<4 | (decimal%10));
}

uint8_t bcd_to_decimal(uint8_t bcd)
{
	return (((bcd>>4)*10) + (bcd&0x0f));
}

void DS1302_TxData(uint8_t txData)	// RTC에 데이터 전송
{
	// 데이터를 하위비트에서 상위비트 순서로 전송
	// 클럭신호를 발생시켜 데이터를 전송
	DS1302_Change_WriteMode();
	for (int i = 0; i < 8; i++)
	{
		// 하위비트부터 상위비트로
		// 1비트 출력하고 클록 올렸다 내린다
		if (txData & (1<<i))
		{
			DS1302_DatabitSet();	// 1이면 실행
		}
		else
		{
			DS1302_DataBitReset();	// 0이면 실행
		}
		
		// 클럭 올렸다 내린다
		DS1302_Clock();
		
	}
}


void DS1302_WiteData(uint8_t address, uint8_t data)
{
	// 주소와 데이터를 전송하고
	// RST 핀을 LOW로 설정
	
	//RST핀을 HIGH로 설정
	DS1302_Selected();
	
	// 주소 전송하고
	DS1302_TxData(address);
	
	// 데이터값 전송
	DS1302_TxData(decimal_to_bcd(data));
	
	// ce(rst) LOW
	DS1302_Deselected();
}

void DS1302_SetTimeData(DS1302 timedata)
{
	DS1302_WiteData(ADDR_SEC, timedata.sec);
	DS1302_WiteData(ADDR_MIN, timedata.min);
	DS1302_WiteData(ADDR_HOUR, timedata.hour);
	DS1302_WiteData(ADDR_DATE, timedata.date);
	DS1302_WiteData(ADDR_MONTH, timedata.month);
	DS1302_WiteData(ADDR_DAYOWEEK, timedata.dayOfweek);
	DS1302_WiteData(ADDR_YEAR ,timedata.year);
}

uint8_t DS1302_RxData()
{
	
	/* 데이터를 하위비트부터 상위비트순으로 읽고
	 * 클럭 신호를 발생시켜서 일는다
	 */
	
	uint8_t rxData = 0;
	DS1302_Change_Readmode();
	for (int i = 0; i < 8; i++)
	{
		//if(DS1302_DATA_PIN & (1 << DS1302_DAT))
			//rxData |= 1<<i;
		//else
			//rxData &= ~(1<<i);
			
			rxData |= (DS1302_DATA_PIN & (1 << DS1302_DAT)) ? (1<<i) : 0; // 삼항연산자
			if( i != 7 ) DS1302_Clock(); // read일때 홀링엣지가 7개임
	}
	
	return rxData;
}

uint8_t DS1302_ReadData(uint8_t address)
{
	// 특정 주소에서 데이터 읽음
	uint8_t rxData = 0;	// 저장 변수
	DS1302_Selected();	// ds1302 선택
	DS1302_TxData(address+1);
	rxData =DS1302_RxData();
	DS1302_Deselected();			// 선택 해제
	return bcd_to_decimal(rxData); // BCD코드를 10진으로 변환
}


void DS1302_GetTime(DS1302 *timedata)
{
	timedata->sec = DS1302_ReadData(ADDR_SEC);
	timedata->min = DS1302_ReadData(ADDR_MIN);
	timedata->hour = DS1302_ReadData(ADDR_HOUR);
}

void DS1302_GetData(DS1302 *timedata)
{
	timedata->date = DS1302_ReadData(ADDR_DATE);
	timedata->month = DS1302_ReadData(ADDR_MONTH);
	timedata->dayOfweek = DS1302_ReadData(ADDR_DAYOWEEK);
	timedata->year = DS1302_ReadData(ADDR_YEAR);
}