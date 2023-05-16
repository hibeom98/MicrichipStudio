


#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>

#define I2C_DDR		DDRD
#define I2C_SCL		PORTD0
#define I2C_SDA		PORTD1

void I2C_Init();
void I2C_Start();
void I2C_Stop();
void I2C_TxData(uint8_t data);
void I2C_TxByte(uint8_t devAddrRW, uint8_t data);


// 사용 안해도 됨
uint8_t I2C_RxDataAck();		//?
uint8_t I2C_RxDataNack();		//?


#endif /* I2C_H_ */
