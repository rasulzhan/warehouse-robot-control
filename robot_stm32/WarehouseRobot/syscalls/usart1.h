#include "stm_lib/inc/stm32f10x_gpio.h"
#include "stm_lib/inc/stm32f10x_rcc.h"
#include "stm_lib/inc/stm32f10x_tim.h"
#include  "stm_lib/inc/stm32f10x_usart.h"
#include  "stm_lib/inc/stm32f10x_exti.h"
#include "stm_lib/inc/stm32f10x_dac.h"
#include "stm_lib/inc/stm32f10x_dma.h"
#include "stm_lib/inc/stm32f10x_pwr.h"
#include "core_cm3.h"


void RCC_Configuration(void) {
	/* --------------------------- System Clocks Configuration -----------------*/
	/* USART1 clock enable */
	RCC_APB2PeriphClockCmd(
			RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,
			ENABLE);

	/* GPIOA clock enable */
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}

/**************************************************************************************/

void GPIO_Configuration(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	/*-------------------------- GPIO Configuration ----------------------------*/

	//TX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//RX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**************************************************************************************/

void USART1_Configuration(void) {
	RCC_Configuration();

	GPIO_Configuration();

	USART_InitTypeDef USART_InitStructure;
//	USART_ClockInitTypeDef USART_ClockInitStructure1;
//
//	USART_ClockStructInit(&USART_ClockInitStructure1);
//	USART_ClockInit(USART1,&USART_ClockInitStructure1);

	/* USARTx configuration ------------------------------------------------------*/
	/* USARTx configured as follow:
	 - BaudRate = 9600 baud
	 - Word Length = 8 Bits
	 - One Stop Bit
	 - No parity
	 - Hardware flow control disabled (RTS and CTS signals)
	 - Receive and transmit enabled
	 */
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;

	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART1, &USART_InitStructure);

	USART_Cmd(USART1, ENABLE);
}


void Usart1Put(uint8_t ch) {
	USART_SendData(USART1, (uint8_t) ~(ch << 1));
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
		;
}

uint8_t Usart1Get(void) {
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
		;
	return (uint8_t) USART_ReceiveData(USART1);
}

void putChar(char ch) {
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
		;
	// Wait for Empty

	USART_SendData(USART1, ~(ch << 1)); // Send 'I'
}

void print(char* str) {
	int length = strlen(str);
	for (int i = 0; i < length; i++) {
		putChar(str[i]);
	}
}
