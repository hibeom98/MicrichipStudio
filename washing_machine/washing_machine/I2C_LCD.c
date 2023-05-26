
#include "I2C_LCD.h"

uint8_t I2C_LCD_Data;

void LCD_Data4bit(uint8_t data)
{	
	I2C_LCD_Data = (I2C_LCD_Data & 0x0f) | (data & 0xf0);		// 상위 4bit 출력
	LCD_EnablePin();
	I2C_LCD_Data = (I2C_LCD_Data & 0x0f) | ((data & 0x0f) << 4); // 하위 4bit 출력
	LCD_EnablePin();	
}

void LCD_EnablePin()
{
	I2C_LCD_Data &= ~(1<<LCD_E);					// E비트를 0 으로 설정
	I2C_TxByte(LCD_DEV_ADDR, I2C_LCD_Data);			// I2C를 통해 LCD의 Enable 핀에 0을 보냄
	
	I2C_LCD_Data |= (1<<LCD_E);					// E비트를 1 으로 설정
	I2C_TxByte(LCD_DEV_ADDR, I2C_LCD_Data);	// I2C를 통해 LCD의 Enable 핀에 1을 보냄
	
	I2C_LCD_Data &= ~(1<<LCD_E);				// E비트를 1 으로 설정
	I2C_TxByte(LCD_DEV_ADDR, I2C_LCD_Data);	// I2C를 통해 LCD의 Enable 핀에 0을 보냄
	_delay_us(1600);
}

void LCD_WriteCommand(uint8_t commadData)
{
	I2C_LCD_Data &= ~(1<<LCD_RS);		// RS비트 0으로 설정
	I2C_LCD_Data &= ~(1<<LCD_RW);	// RW 비트 0으로 설정/////
	LCD_Data4bit(commadData);			// LCD 명령을 보냄
}

void LCD_WriteData(uint8_t charData)	
{
	I2C_LCD_Data |= (1<<LCD_RS);		// RS비트 1으로 설정
	I2C_LCD_Data &= ~(1<<LCD_RW);	// RW 비트 0으로 설정////
	LCD_Data4bit(charData);				// LCD 에 문자 데이터 보냄
}

void LCD_BackLightOn()
{
	I2C_LCD_Data |= (1<<LCD_BACKLIGHT);
	I2C_TxByte(LCD_DEV_ADDR, I2C_LCD_Data);	// I2C를 통해 LCD의 백라이트를 켭니다
}

void LCD_GotoXY(uint8_t row, uint8_t col)
{
	col %= 16;
	row %= 2;
	
	uint8_t address = (0x40 * row) + col;	 // 지정된 행과 열의 LCD 주소를 계산합니다.
	uint8_t command = 0x80 + address;
	LCD_WriteCommand(command);				// 커서 위치를 설정하는 LCD 명령을 작성합니다.
}

void LCD_WriteString(char *string)
{
	for (uint8_t i=0; string[i]; i++)
	{
		LCD_WriteData(string[i]);
	}
}

void LCD_WriteStringXY(uint8_t row, uint8_t col, char *string)
{
	LCD_GotoXY(row, col);		// 커서를 지정된 행과 열로 이동합니다.
	LCD_WriteString(string);
}

void LCD_Init()
{
	I2C_Init();
	
	_delay_ms(50);
	LCD_WriteCommand(0x03);
	_delay_ms(10);
	LCD_WriteCommand(0x03);
	_delay_ms(1);
	LCD_WriteCommand(0x03);
	
	LCD_WriteCommand(0x02);
	LCD_WriteCommand(COMMAND_4_BIT_MODE);
	LCD_WriteCommand(COMMAND_DISPLAY_OFF);
	LCD_WriteCommand(COMMAND_DISPLAY_CLEAR);
	LCD_WriteCommand(COMMAND_ENTRY_MODE);
	LCD_WriteCommand(COMMAND_DISPLAY_ON);
	LCD_BackLightOn();
}

