
#include "I2C.h"

void I2C_Init()
{
	I2C_DDR |= (1<<I2C_SCL)|(1<<I2C_SDA);		// I2C핀을 출력으로 설정
	TWBR = 72; //100kHz
	//TWBR = 32; //200kHz
	//TWBR = 12; //400kHz
}
void I2C_Start()
{	
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);		// TWCR 레지스터의 START비트를 설정	
	while (!(TWCR &	(1<<TWINT)));	//하드웨어가 TWINT세트되는 시점을 결정하므로 약간의 시간이 걸림
}

void I2C_Stop()
{	
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);	//TWCR의 STOP 비트 설정
}

void I2C_TxData(uint8_t data)		// 데이터 한 바이트 보냄
{
	TWDR = data;					// 데이터를 TWDR 레지스터에 로드
	TWCR = (1<<TWINT) |	(1<<TWEN);	// 데이터 전송을 시작하기 위해 TWCR 레지스트의 TWINT 비트 세트	
	
	/* Wait for TWINT Flag set. 
	This indicates that the DATA has been transmitted, and
	ACK/NACK has been received.*/
	while (!(TWCR &	(1<<TWINT)));
}

void I2C_TxByte(uint8_t devAddrRW, uint8_t data)
{
	I2C_Start();
	I2C_TxData(devAddrRW);
	I2C_TxData(data);
	I2C_Stop();
}

// 사용 안해도 됨
uint8_t I2C_RxDataAck()			// 안해도 됨 I2C 모듈은 하드웨어에서 처리함
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);	// ACK 비트 설정
	while(!(TWCR & (1<<TWINT)));			// 데이터 수신이 완료될 때까지 대기
	
	return TWDR;
}

uint8_t I2C_RxDataNack()		//?  안해도 됨 I2C 모듈은 하드웨어에서 처리함
{
	TWCR = (1<<TWINT)|(1<<TWEN);			// ACK 비트 삭제
	while(!(TWCR & (1<<TWINT)));			// 데이터 수신이 완료될 때까지 대기
	
	return TWDR;
}