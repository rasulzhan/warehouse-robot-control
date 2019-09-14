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
/***************END ADD LCD Libraries CONNECTION*****************************************/
static int ALL_POWER = 0;

void USART_Configuration(void);

/************Function Declarations*******************************************************/
void RegisterAdcInit(void); // инициализация настроек АЦП, но возможно использование только одного порта
void AdcInit(void); // инициализация настроек АЦП, необходимо перед тем как считывать значения с АЦП
void LcdInit(void); // инициализация настроек экрана
void PwmInit(void); // инициализация настроек ШИМ (Широтного Импульсного модулятора)
void USART1_Configuration();

void delay_microseconds(uint16_t us);
uint32_t uint32_time_diff(uint32_t now, uint32_t before);
void hd44780_assert_failure_handler(const char *filename, unsigned long line);
uint16_t Read_ADC1(uint8_t channel); // считывание значений с АЦП
/****************************************************************************************/

/*************LCD object*****************************************************************/
HD44780 lcd;
HD44780_STM32F10x_GPIO_Driver lcd_pindriver;
/****************************************************************************************/

/************************************timer***********************************************/
volatile uint32_t systick_ms = 0;

double speed(double r) {
	return sin(r);
}

uint16_t pwmConvertor(int value) {
	return 65535 - (65535 * value / 100);
}

void initDriverGPIO() {
	//1 - left c0
	//1 - right c1
	//2 - left  c2
	//3 - right c3
	//left c4
	//right c5
	// button a left c6
	//button a right c7
	// button b left c8
	// button b right c9

	//b3, b4, b5
	GPIO_InitTypeDef GPIO_InitStructuress;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	//Включем порт А
	GPIO_InitStructuress.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2
			| GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5
			| GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12
			| GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructuress.GPIO_Mode = GPIO_Mode_IPD;

	GPIO_InitStructuress.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructuress);

	GPIO_InitTypeDef buttons;
	buttons.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
	buttons.GPIO_Mode = GPIO_Mode_IPD;
	buttons.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&buttons);


	GPIO_InitTypeDef gpiob;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	//Включем порт B
	gpiob.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	gpiob.GPIO_Mode = GPIO_Mode_Out_PP;
	gpiob.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpiob);
}

void ButtonInit(void);
void AButtonInit();

void Usart1Put(uint8_t ch) {
	USART_SendData(USART1, (uint8_t) ~(ch << 1));
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
		;
}

uint8_t Usart1Get(void) {
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
		;
	uint8_t ch = (uint8_t) USART_ReceiveData(USART1);
	if (ch >= 64) {
		return ~(ch << 1);
	} else if (ch >= 32) {
		return (63 - ch) * 4 + 2;
	} else if (ch >= 16) {
		return (31 - ch) * 8 + 4;
	} else if (ch >= 8) {
		return (15 - ch) * 16 + 8;
	} else if (ch >= 4) {
		return (7 - ch) * 32 + 16;
	} else if (ch >= 2) {
		return (3 - ch) * 64 + 32;
	} else if (ch >= 1) {
		return (1 - ch) * 128 + 64;
	} else
		return 0;
}

uint8_t receiveUartData(void) {
	uint8_t ch = (uint8_t) USART_ReceiveData(USART1);
	if (ch >= 64) {
		return ~(ch << 1);
	} else if (ch >= 32) {
		return (63 - ch) * 4 + 2;
	} else if (ch >= 16) {
		return (31 - ch) * 8 + 4;
	} else if (ch >= 8) {
		return (15 - ch) * 16 + 8;
	} else if (ch >= 4) {
		return (7 - ch) * 32 + 16;
	} else if (ch >= 2) {
		return (3 - ch) * 64 + 32;
	} else if (ch >= 1) {
		return (1 - ch) * 128 + 64;
	} else
		return 0;
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

/*******************************LCD timer**********************************************/
void SysTick_Handler(void) {
	++systick_ms;
}

/****************настройка LCD *******************************************************/
void LcdInit(void) {
	/* Распиновка дисплея */
	const HD44780_STM32F10x_Pinout lcd_pinout = { {
	/* RS        */{ GPIOA, GPIO_Pin_6 },
	/* ENABLE    */{ GPIOA, GPIO_Pin_5 },
	/* RW        */{ GPIOA, GPIO_Pin_4 },
	/* Backlight */{ NULL, 0 },
	/* DP0       */{ NULL, 0 },
	/* DP1       */{ NULL, 0 },
	/* DP2       */{ NULL, 0 },
	/* DP3       */{ NULL, 0 },
	/* DP4       */{ GPIOA, GPIO_Pin_3 },
	/* DP5       */{ GPIOA, GPIO_Pin_2 },
	/* DP6       */{ GPIOA, GPIO_Pin_1 },
	/* DP7       */{ GPIOA, GPIO_Pin_0 }, } };

	/* Настраиваем драйвер: указываем интерфейс драйвера (стандартный),
	 указанную выше распиновку и обработчик ошибок GPIO (необязателен). */
	lcd_pindriver.interface = HD44780_STM32F10X_PINDRIVER_INTERFACE;
	/* Если вдруг захотите сами вручную настраивать GPIO для дисплея
	 (зачем бы вдруг), напишите здесь ещё (библиотека учтёт это):
	 lcd_pindriver.interface.configure = NULL; */
	lcd_pindriver.pinout = lcd_pinout;
	lcd_pindriver.assert_failure_handler = hd44780_assert_failure_handler;

	/* И, наконец, создаём конфигурацию дисплея: указываем наш драйвер,
	 функцию задержки, обработчик ошибок дисплея (необязателен) и опции.
	 На данный момент доступны две опции - использовать или нет
	 вывод RW дисплея (в последнем случае его нужно прижать к GND),
	 и то же для управления подсветкой. */
	const HD44780_Config lcd_config = {
			(HD44780_GPIO_Interface*) &lcd_pindriver, delay_microseconds,
			hd44780_assert_failure_handler, HD44780_OPT_USE_RW };

	/* Ну, а теперь всё стандартно: подаём тактирование на GPIO,
	 инициализируем дисплей: 16x2, 4-битный интерфейс, символы 5x8 точек. */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	hd44780_init(&lcd, HD44780_MODE_4BIT, &lcd_config, 16, 2,
			HD44780_CHARSIZE_5x8);
}

//********************************************************************************************
//function инициализация АЦП                                                                //
//argument none                                                                             //
//return   none                                                                             //
//********************************************************************************************
void RegisterAdcInit(void) {
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // Разрешить тактирование порта PORTA
	//Конфигурирование PORTA.6 - аналоговый вход
	GPIOA->CRL &= ~GPIO_CRL_MODE7; //Очистить биты MODE
	GPIOA->CRL &= ~GPIO_CRL_CNF7; //Очистить биты CNF

	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; //подаем тактирование АЦП
	RCC->CFGR &= ~RCC_CFGR_ADCPRE; //входной делитель
	ADC1->CR1 = 0; //
	ADC1->SQR1 = 0; //
	ADC1->CR2 |= ADC_CR2_CAL; //запуск калибровки
	while (!(ADC1->CR2 & ADC_CR2_CAL)) {
	}; //ждем окончания калибровки
	ADC1->CR2 = ADC_CR2_EXTSEL; //выбрать источником запуска разряд  SWSTART
	ADC1->CR2 |= ADC_CR2_EXTTRIG; //разр. внешний запуск регулярного канала
	ADC1->CR2 |= ADC_CR2_CONT; //режим непрерывного преобразования
	ADC1->SQR3 = 7; //загрузить номер канала
	ADC1->CR2 |= ADC_CR2_ADON; //включить АЦП
	ADC1->CR2 |= ADC_CR2_SWSTART; //запустить процес преобразования

	// adc2
//	RCC->APB2ENR |= RCC_APB2ENR_IOPDEN; // Разрешить тактирование порта PORTB
//	GPIOB->CRL &= ~GPIO_CRL_MODE7; //Очистить биты MODE
//	GPIOB->CRL &= ~GPIO_CRL_CNF7; //Очистить биты CNF

}

void AdcInit(void) {

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	/* Сконфигурируем  порты для  приема аналогового сигнала A0,A1,A2,A3     */
	GPIO_InitTypeDef GPIO_InitStructurea;
	GPIO_InitStructurea.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructurea.GPIO_Mode = GPIO_Mode_AIN;

	GPIO_Init(GPIOA, &GPIO_InitStructurea);

	//клок на порт A
//	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	/* Сконфигурируем  порты для  приема аналогового сигнала A0,A1,A2,A3     */
	GPIO_InitTypeDef GPIO_InitStructurest;
	GPIO_InitStructurest.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructurest.GPIO_Mode = GPIO_Mode_AIN;
	;
	GPIO_Init(GPIOC, &GPIO_InitStructurest);

	ADC_InitTypeDef ADC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	// ADC1 структура инициализации
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE; //Мы сами будем все переключать
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //Когда нам это будет надо
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 4; //у нас 4 канала
	ADC_Init(ADC1, &ADC_InitStructure);

	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);

	//Калибровка
	/* Enable ADC1 reset calibration register */
	ADC_ResetCalibration(ADC1);
	/* Check the end of ADC1 reset calibration register */
	while (ADC_GetResetCalibrationStatus(ADC1))
		;

	/* Start ADC1 calibration */
	ADC_StartCalibration(ADC1);
	/* Check the end of ADC1 calibration */
	while (ADC_GetCalibrationStatus(ADC1))
		;

}

void PwmInit(void) {

	//B1 - A2
	//B0 - A1

	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	//DIRECTION
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//Включем порт А
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	//Включаем Таймер 2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	GPIO_InitTypeDef PORT;
	// Настроим ноги со светодиодами на выход
	PORT.GPIO_Pin = (GPIO_Pin_0 | GPIO_Pin_1);
	//Будем использовать альтернативный режим а не обычный GPIO
	PORT.GPIO_Mode = GPIO_Mode_AF_PP;
	PORT.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &PORT);
	//Разрешаем таймеру использовать ноги PA1,PA2,PA3 для ШИМа
	TIM3->CCER |= (TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E);
	// Для всех трех каналов задаем инверсный ШИМ.
	TIM3->CCMR1 |= (TIM_CCMR1_OC2M_0 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2);
	TIM3->CCMR2 |= (TIM_CCMR2_OC3M_0 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2
			| TIM_CCMR2_OC4M_0 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2);
	//Запускаем таймер!
	TIM3->CR1 |= TIM_CR1_CEN;
	//После этого пишем данные в TIM2->CCRx - и яркость светодиодов меняется
}

//reading selected channel
uint16_t Read_ADC1(uint8_t channel) {
	//номер АЦП, канал и время преобразования
	ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_41Cycles5);
	// Пуск преобразования
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	// ждем
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
		;
	// Результат
	return ADC_GetConversionValue(ADC1);
}

void delay_ms(uint32_t ms) {
	volatile uint32_t nCount;
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);
	nCount = (RCC_Clocks.HCLK_Frequency / 10000) * ms;
	for (; nCount != 0; nCount--)
		;
}

void delay_microseconds(uint16_t us) {
	SysTick->VAL = SysTick->LOAD;
	const uint32_t systick_ms_start = systick_ms;

	while (1) {
		uint32_t diff = uint32_time_diff(systick_ms, systick_ms_start);

		if (diff >= ((uint32_t) us / 1000) + (us % 1000 ? 1 : 0))
			break;
	}
}

uint32_t uint32_time_diff(uint32_t now, uint32_t before) {
	return (now >= before) ? (now - before) : (UINT32_MAX - before + now);
}

void hd44780_assert_failure_handler(const char *filename, unsigned long line) {
	(void) filename;
	(void) line;
	do {
	} while (1);
}

void USART_Configuration(void) {
	/***************RCC**************************/
	// clock for GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	/* Enable UART clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	/**********************GPIO*******************/
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Configure USART Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; // PA.09 USART1.TX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure USART Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; // PA.10 USART1.RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitTypeDef USART_InitStructure;

	/* USART configured as follow:
	 - BaudRate = 115200 baud
	 - Word Length = 8 Bits
	 - One Stop Bit
	 - No parity
	 - Hardware flow control disabled (RTS and CTS signals)
	 - Receive and transmit enabled
	 */
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_2;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/* USART configuration */
	USART_Init(USART1, &USART_InitStructure);

	/* Enable the USART1 */
	USART_Cmd(USART1, ENABLE);
}

void interrupt_init(void) {

	NVIC_SetPriority(EXTI0_IRQn, 15);
	NVIC_EnableIRQ(EXTI0_IRQn);
}

//-----------------------------------------------------------------------------
void handler_exti0(void) {
	if (GPIOA->IDR == 1) {
		//work
		GPIOC->ODR = GPIOC->ODR | GPIO_Pin_9;
		ALL_POWER++;
	} else {
		//don't work
//		GPIOC->ODR &= !(GPIOC->ODR^GPIO_Pin_9);
	}
	EXTI->PR = EXTI_PR_PR0;
}

void ButtonInit(void) {
	GPIO_InitTypeDef GPIO_InitStructuress;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//Включем порт А
	GPIO_InitStructuress.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructuress.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructuress.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructuress);

	interrupt_init();

	EXTI->IMR &= ~EXTI_IMR_MR0;
	EXTI->EMR &= ~EXTI_EMR_MR0;

	//Разрешаем Тактирование порта
	RCC->APB2ENR = RCC_APB2ENR_AFIOEN;

	//Выбираев вход
	AFIO->EXTICR[0] &= ~AFIO_EXTICR1_EXTI0_PA;
	AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PA;

	// Выбираем детектирование оба фронта
	EXTI->RTSR |= EXTI_RTSR_TR0;
	EXTI->FTSR |= EXTI_FTSR_TR0;

	//Разрешаем генерацию прерывания от выбранной линии
	EXTI->IMR |= EXTI_IMR_MR0;
}

void AButtonInit(void) {
	GPIO_InitTypeDef GPIO_InitStructuress;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//Включем порт А
	GPIO_InitStructuress.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructuress.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructuress.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructuress);
}

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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
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
