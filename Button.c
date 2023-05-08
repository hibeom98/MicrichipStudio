#include "Button.h"	//버튼 관련 헤더파일 읽어오기

/* 버튼 구조체 초기화 함수 */
void Button_Init(Button *button, volatile uint8_t *ddr,
				  volatile uint8_t *pin, uint8_t pinNumber)
{

	/*(Button.ddrReg)*/
	button->ddrReg = ddr;						// 구조체 멤버인 ddrReg 포인터 변수에 ddr 주소 할당
	button->pinReg = pin;						// 구조체 멤버인 pinReg 포인터 변수에 PIN 주소 할당
	button->btnPin = pinNumber;					// 구조체 멤버인 btnPin에 핀번호 저장
	button->previousState = RELEASED;			// 구조체 멤버인 previousState를 RELEASED로 초기화
	*button->ddrReg &= ~(1<<button -> btnPin);	// DDR 레지스터에서 버튼 핀을 입력으로 설정
}

/* 버튼 상태를 확인하고 액션을 반환하는 함수 */
uint8_t Button_GetState(Button *button)
{
	/* 현재 버튼 핀의 상태를 읽어옴 */
	uint8_t currentState = *button -> pinReg & (1 << button ->btnPin);
	
	/* 버튼이 눌렸을때 */
	if ((currentState == PUSHED) && (button -> previousState == RELEASED))
	{
		_delay_ms(50);							// 디바운스 코드		
		button -> previousState =PUSHED;		// 이전 버튼 상태를 눌린 상태로 갱신
		return PUSHED_ACTION;					// PUSHED_ACTION값 반환
	}
	
	/*버튼이 떨어졌을때*/	
	else if ((currentState != PUSHED) && (button->previousState == PUSHED))
	{
		_delay_ms(50);
		button->previousState = RELEASED;		// 이전 버튼 상태를 떨어진 상태로 갱신
		return RELEASED_ACTION;					// RELEASED_ACTION값 반환
	}
	return NO_ACTION;							//액션이 없을 때 NO_ACTION반환
}
