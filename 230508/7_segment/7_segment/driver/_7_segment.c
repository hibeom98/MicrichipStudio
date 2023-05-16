#include "_7_segment.h"

void FND_Display(uint16_t data)
{
	static uint8_t position = 0;
	uint8_t fnddata [10]						//FND데이터 배열 저장
	={0x3f, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};
	
	switch(position)							// 현재 출력할 자리에 따라 해당 자리의 FND 출력
	{
		case 0:									// 첫번째자리 FND출력을 위해 첫번째핀 LOW, 나머지핀 HIGH 설정
		FND_SELECT_PORT &= ~(1<<3);				// digit 1번 on
		FND_SELECT_PORT |=(1<<0)|(1<<1)|(1<<2);	// digit 2,3,4, off
		FND_DATA_PORT = fnddata[data/1000];		// 천의 자리를 구하여 해당 FND 출력
		break;
		
		case 1:									// 3번째자리 FND출력을 위해 첫번째핀 LOW, 나머지핀 HIGH 설정
		FND_SELECT_PORT &= ~(1<<2);				// digit 2번 on
		FND_SELECT_PORT |=(1<<0)|(1<<1)|(1<<3);	// digit 1,3,4, off
		FND_DATA_PORT = fnddata[data/100%10];		// 백의 자리를 구하여 해당 FND 출력
		break;
		
		case 2:									// 세번째자리 FND출력을 위해 첫번째핀 LOW, 나머지핀 HIGH 설정
		FND_SELECT_PORT &= ~(1<<1);				// digit 3번 on
		FND_SELECT_PORT |=(1<<0)|(1<<2)|(1<<3);	// digit 1,2,4, off
		FND_DATA_PORT = fnddata[data/10%10];	// 십의 자리를 구하여 해당 FND 출력
		break;
		
		case 3:									// 네번째자리 FND출력을 위해 첫번째핀 LOW, 나머지핀 HIGH 설정
		FND_SELECT_PORT &= ~(1<<0);				// digit 4번 on
		FND_SELECT_PORT |=(1<<1)|(1<<2)|(1<<3);	// digit 1,2,3 off
		FND_DATA_PORT = fnddata[data%10];		// 일의 자리를 구하여 해당 FND 출력
		break;
		/*c*/
	}
	position++;									// 다음자리 이동을 위해 position 증가
	position = position %4;						// 4자리를 출력한 후 다시 첫번째로 돌아가기 위해
	// position 값을 4로 나눈 나머지 값을 저장
}