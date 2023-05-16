

#ifndef ULED_H_
#define ULED_H_

void UART0_init(void);
void UART0_transmit(char data);	     //UART가 2개인데 그 중에서 우리는 0번을 쓸 꺼라서 0을 붙인다.
unsigned char UART0_receive(void);   //초기화 하는 함수                    //데이터 시트 191p




#endif /* ULED_H_ */