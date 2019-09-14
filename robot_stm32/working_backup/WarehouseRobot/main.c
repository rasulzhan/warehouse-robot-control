#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include <string.h>
/***************ADD ADC Library*********************************************************/
#include "stm_lib/inc/stm32f10x_adc.h"
/***************ADD ADC Library*********************************************************/

#include "stm_lib/inc/stm32f10x_gpio.h"
#include "stm_lib/inc/stm32f10x_rcc.h"
#include "stm_lib/inc/stm32f10x_tim.h"
#include "stm_lib/inc/stm32f10x_usart.h"
#include "stm_lib/inc/stm32f10x_exti.h"
#include "stm_lib/inc/stm32f10x_dac.h"
#include "stm_lib/inc/stm32f10x_dma.h"
#include "stm_lib/inc/stm32f10x_pwr.h"
#include "core_cm3.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/***************START ADD LCD Libraries CONNECTION***************************************/
#include "lcdlib/hd44780.h"
#include "lcdlib/drivers/hd44780_stm32f10x.h"

#include "move.h"

#define speed15 pwmConvertor(15)
#define speed7	pwmConvertor(8)

void defaultSpeed(uint16_t *speed0, uint16_t* speed1) {
	*speed0 = speed15;
	*speed1 = speed7;
}

//C0 - передний левый
//C1 - передний правый
//C2 - задний левый
//C3 - задний правый
//C4 - левый
//C5 - правый

/****************MAIN FUNCTION***********************************************************/
int main(void) {
//	PwmInit();
//
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOC,&GPIO_InitStructure);

//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//	GPIO_InitTypeDef motor1;
//	motor1.GPIO_Mode = GPIO_Mode_Out_PP;
//	motor1.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
//	motor1.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB,&motor1);

//	int speed00 = 65535 - (65535 * value / 100);
//	int speed00 = 65535;
//	int speed100 = 60000;
//	TIM3->CCR3 = speed00;
//
//	TIM3->CCR4 = speed00;
//	while(1) {
//		int c0 = !!(GPIOC->IDR&63);
//		if(c0 == 1) {
//			TIM3->CCR3 = speed100;
//			TIM3->CCR4 = speed100;
////			GPIOB->ODR = 3;
//		}else {
//			TIM3->CCR3 = speed00;
//			TIM3->CCR4 = speed00;
////			GPIOB->ODR = 0;
//		}
//	}
//	return 0;
	initDriverGPIO();
	PwmInit();
//	AButtonInit();
	USART1_Configuration();

	stop();
	uint16_t speed0 = speed15;
	uint16_t speed1 = speed7;
//	while(1){
//		char* buff = "Done\n";
//		print(buff);
//	}
//
//	int command = STOP;
//	while (1) {
//		if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET) {
//			command = receiveUartData();
//			speed0 = speed15;
//			speed1 = speed7;
//		}
//		switch (command) {
//		case STOP:
//			stop();
//			defaultSpeed(&speed0, &speed1);
//			break;
//		case MOVE_FORWARD:
//			move_forward(&speed0, &speed1);
//			defaultSpeed(&speed0, &speed1);
//			break;
//		case MOVE_BACK:
//			move_back1(&speed0, &speed1);
//			defaultSpeed(&speed0, &speed1);
//			break;
//		case MOVE_2_FORWARD:
//			move_2forward(&speed0, &speed1);
//			defaultSpeed(&speed0, &speed1);
//			break;
//		case MOVE_FORWARD_BUTTON:
//			move_forwardButton(&speed0, &speed1);
//			defaultSpeed(&speed0, &speed1);
//			break;
//		case MOVE_BACK_BUTTON:
//			move_backButton(&speed0, &speed1);
//			defaultSpeed(&speed0, &speed1);
//			break;
//		case TURN_RIGHT:
//			turnRight(&speed0, &speed1);
//			defaultSpeed(&speed0, &speed1);
//			break;
//		case TURN_LEFT:
//			turnLeft(&speed0, &speed1);
//			defaultSpeed(&speed0, &speed1);
//			break;
//		case TURN_BACK_LEFT:
//			turnBackLeft(&speed0, &speed1);
//			defaultSpeed(&speed0, &speed1);
//			break;
//		case TURN_BACK_RIGHT:
//			turnBackRight(&speed0, &speed1);
//			defaultSpeed(&speed0, &speed1);
//			break;
//		default:
//			stop();
//			defaultSpeed(&speed0, &speed1);
//			break;
//		}
//	}

	move_forward(&speed0, &speed1);
	defaultSpeed(&speed0, &speed1);

	start:
	small_move_forward();
	move_forward(&speed0, &speed1);
	defaultSpeed(&speed0, &speed1);

//	small_move_forward();
	turnRightDelay(&speed0, &speed1);

	turnRight(&speed0, &speed1);
	defaultSpeed(&speed0, &speed1);

	move_forward(&speed0, &speed1);
	defaultSpeed(&speed0, &speed1);

//	small_move_forward();
	turnLeftDelay(&speed0, &speed1);

	turnLeft(&speed0, &speed1);
	defaultSpeed(&speed0, &speed1);

	small_move_forward();

	move_forward(&speed0, &speed1);
	defaultSpeed(&speed0, &speed1);

//	small_move_forward();
	turnRightDelay(&speed0, &speed1);

	turnRight(&speed0, &speed1);
	defaultSpeed(&speed0, &speed1);

	move_forwardButton(&speed0, &speed1);
	defaultSpeed(&speed0, &speed1);

	shavtit_perednyu();
	podem_kleshnei();

	move_back1(&speed0, &speed1);
	defaultSpeed(&speed0, &speed1);

	turnRightDelay(&speed0, &speed1);
	turnRight(&speed0, &speed1);
	defaultSpeed(&speed0, &speed1);

	small_move_forward();
	move_forward(&speed0, &speed1);
	defaultSpeed(&speed0, &speed1);

	turnRightDelay(&speed0, &speed1);
	turnRight(&speed0, &speed1);
	defaultSpeed(&speed0, &speed1);

	small_move_forward();
	move_forward(&speed0, &speed1);
	defaultSpeed(&speed0, &speed1);

	turnLeftDelay(&speed0, &speed1);
	turnLeft(&speed0, &speed1);
	defaultSpeed(&speed0, &speed1);

	small_move_forward();
	move_forward(&speed0, &speed1);
	defaultSpeed(&speed0, &speed1);

	move_forwardButton(&speed0, &speed1);
	defaultSpeed(&speed0, &speed1);
	brosit_perednyu();

	stop();
	opustit_kleshni();

	small_move_back();
	move_back1(&speed0, &speed1);
	defaultSpeed(&speed0, &speed1);


	turnLeftDelay(&speed0, &speed1);
	turnLeft(&speed0, &speed1);
	turnLeftDelay(&speed0, &speed1);
	turnLeft(&speed0, &speed1);
	goto start;



	return 0;
//	//small_move_back();
//	turnBackLeftDelay(&speed0, &speed1);
//	turnBackLeft(&speed0, &speed1);
//	defaultSpeed(&speed0, &speed1);
//
//	move_back1(&speed0, &speed1);
//	defaultSpeed(&speed0, &speed1);
//
//	turnBackRightDelay(&speed0, &speed1);
//	turnBackRight(&speed0, &speed1);
//	defaultSpeed(&speed0, &speed1);
//
//	small_move_back();
//
//	move_back1(&speed0, &speed1);
//	defaultSpeed(&speed0, &speed1);
//
//	small_move_back();
//	turnBackLeft(&speed0, &speed1);
//	defaultSpeed(&speed0, &speed1);
//
//	small_move_back();
//	move_back1(&speed0, &speed1);
//	defaultSpeed(&speed0, &speed1);
//
//	turnLeft(&speed0, &speed1);
//	turnLeft(&speed0, &speed1);
//	small_move_forward();
//
//	move_forwardButton(&speed0, &speed1);
//	defaultSpeed(&speed0, &speed1);
//
//	brosit_perednyu();
//	opustit_kleshni();

	return 0;
//	int command = MOVE_FORWARD;
//	while (1) {
//		if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET) {
//			command = receiveUartData();
//			speed0 = pwmConvertor(15);
//			speed1 = pwmConvertor(7);
//		}
//		switch (command) {
//		case STOP:
//			stop();
//			break;
//		case MOVE_FORWARD:
//			move_forward(&speed0, &speed1);
//			break;
//		case MOVE_BACK:
//			move_back(&speed0, &speed1);
//			break;
//		case MOVE:
//			move();
//			break;
//		default:
//			stop();
//			break;
//		}
//	}
}
