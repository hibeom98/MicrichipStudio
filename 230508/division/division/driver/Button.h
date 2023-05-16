
//헤더파일 중복 방지
#ifndef BUTTON_H_       //만약 BUTTON_H_가 정의 되어 있지 않으면
#define BUTTON_H_              //BUTTON_H_를 정의한다.

#define F_CPU 16000000UL
#include <stdio.h>
#include <util/delay.h>

//1번은 켜지는 거 2번은 꺼지는 거 3번은 껏다켯다(토글)

enum 
   {
   PUSHED,   //버튼 눌림 상태  0        enum은 항상 위에서 부터 index를 가지고 있다.
   RELEASED  //버튼 놓기 상태  1
   };

enum
   {
   NO_ACTION,    //버튼 동작이 없을 액션
   PUSHED_ACTION, //버튼이 눌려있는 액션
   RELEASED_ACTION  //버튼을 놓은 액션
   };
   
#define LED_DDR  DDRA   //LED출력 포트 방향
#define LED_PORT PORTA  //LED출력 포트
#define BUTTON_DDR DDRD  //BUTTON 방향
#define BUTTON_PIN PIND //BUTTON 핀
#define BUTTON_ON 0     //버튼 ON상태를 나타낼 꺼(연결 핀 번호)
#define BUTTON_OFF 1   
#define BUTTON_TOGGLE 2

//구조체 정의
typedef struct _button
{
   volatile uint8_t *ddrReg;  //포트방향 레지스터 포인터 변수
   volatile uint8_t *pinReg;  //입력핀 포인터 변수
   uint8_t btnPin;            //버튼 입력 핀 번호
   uint8_t previousState;     //이전 버튼 상태 변수
   }Button;  


//버튼 초기화 함수 정의
void Button_Init(Button *button, volatile uint8_t *ddr, 
                  volatile uint8_t *pin, uint8_t pinNumber);   //4개를 넘긴다.     //이걸 불러오는 것만으로 초기화 시킬 꺼다.

//버튼의 상태 확인 함수 정의
uint8_t Button_GetState(Button *button);
   


#endif /* BUTTON_H_ */  //BUTTON_H_를 종료한다.