#include "myutils.h"

#define STOP '1'
#define MOVE_FORWARD '2'
#define MOVE_BACK '3'
#define MOVE_2_FORWARD '4'
#define MOVE_FORWARD_BUTTON '5'
#define MOVE_BACK_BUTTON '6'
#define TURN_RIGHT '7'
#define TURN_LEFT '8'
#define TURN_BACK_LEFT '9'
#define TURN_BACK_RIGHT 'A'

#define speed_5 pwmConvertor(7)
#define speed_2	pwmConvertor(5)
#define speed_20 pwmConvertor(10)

#define SENSOR_LEFT_A "SENSOR_LEFT_A\n"
#define SENSOR_RIGHT_A "SENSOR_RIGHT_A\n"
#define SENSOR_LEFT_B "SENSOR_LEFT_B\n"
#define SENSOR_RIGHT_B "SENSOR_RIGHT_B\n"
#define SENSOR_LEFT_C "SENSOR_LEFT_C\n"
#define SENSOR_RIGHT_C "SENSOR_RIGHT_C\n"

#define SENSOR_A "SENSOR_A\n"
#define SENSOR_B "SENSOR_B\n"
#define SENSOR_C "SENSOR_C\n"

#define SENSOR_A_FORWARD "SENSOR_A_FORWARD\n"
#define SENSOR_B_FORWARD "SENSOR_B_FORWARD\n"
#define SENSOR_C_FORWARD "SENSOR_C_FORWARD\n"

#define SENSOR_A_BACK "SENSOR_A_BACK\n"
#define SENSOR_B_BACK "SENSOR_B_BACK\n"
#define SENSOR_C_BACK "SENSOR_C_BACK\n"
#define DONE "DONE\n"

uint16_t pwmConvertor(int);

#define PWM_20  pwmConvertor(50)
#define PWM_10  pwmConvertor(25)
#define PWM_5  pwmConvertor(11)
#define PWM_0  pwmConvertor(0)
#define PWM_2  pwmConvertor(5)

void sensorCheck() {
	int aLeft = !(!(GPIOC->IDR & 1)); // Port C0
	int aRight = !(!(GPIOC->IDR & 2)); // Port C1
	int bLeft = !(!(GPIOC->IDR & 4)); // Port C2
	int bRight = !(!(GPIOC->IDR & 8)); // Port C3
	int leftSensor = !(!(GPIOC->IDR & 16)); // Port C4
	int rightSensor = !(!(GPIOC->IDR & 32)); // Port C5
	int aLeftButton = !(!(GPIOC->IDR & 64)); // Port C6
	int aRightButton = !(!(GPIOC->IDR & 128)); // Port C7
	int bLeftButton = !(!(GPIOC->IDR & 256)); // Port C8
	int bRightButton = !(!(GPIOC->IDR & 512)); // Port C9
}

void move_forward(uint16_t* speed0, uint16_t* speed1) {
	while (1) {
		int aLeft = !(!(GPIOC->IDR & 1)); // Port C0
		int aRight = !(!(GPIOC->IDR & 2)); // Port C1

		int leftSensor = !(!(GPIOC->IDR & 16)); // Port C4
		int rightSensor = !(!(GPIOC->IDR & 32)); // Port C5

		if ((leftSensor == 1) && (rightSensor == 1)) {
			GPIOA->ODR &= (GPIOA->ODR ^ 2);
			GPIOA->ODR &= (GPIOA->ODR ^ 4);

			TIM3->CCR3 = PWM_0;
			TIM3->CCR4 = PWM_0;
			break;
		}

		if ((aLeft == 1) && (aRight == 1)) {
			*speed0 = speed_5;
			*speed1 = speed_2;
		} else if (aLeft == 1) {
			GPIOA->ODR &= (GPIOA->ODR ^ 2);
			GPIOA->ODR &= (GPIOA->ODR ^ 4);

			TIM3->CCR3 = *speed0;
			TIM3->CCR4 = *speed1;
		} else if (aRight == 1) {
			GPIOA->ODR &= (GPIOA->ODR ^ 2);
			GPIOA->ODR &= (GPIOA->ODR ^ 4);

			TIM3->CCR3 = *speed1;
			TIM3->CCR4 = *speed0;
		} else {
			GPIOA->ODR &= (GPIOA->ODR ^ 2);
			GPIOA->ODR &= (GPIOA->ODR ^ 4);

			TIM3->CCR3 = *speed0;
			TIM3->CCR4 = *speed0;
		}
	}
	char * done = DONE;
	print(done);
	delay_ms(1400);
}

void move_forwardButton(uint16_t* speed0, uint16_t* speed1) {
	while (1) {
		int aLeft = !(!(GPIOC->IDR & 1)); // Port C0
		int aRight = !(!(GPIOC->IDR & 2)); // Port C1

		int aButton = !(!(GPIOC->IDR & 64)); // Port C6
//		int bButton = !(!(GPIOC->IDR & 128)); // Port C7

		int leftSensor = !(!(GPIOC->IDR & 16)); // Port C4
		int rightSensor = !(!(GPIOC->IDR & 32)); // Port C5

		if ((aLeftButton == 1) && (aRightButton == 1)) {
			GPIOA->ODR &= (GPIOA->ODR ^ 2);
			GPIOA->ODR &= (GPIOA->ODR ^ 4);

			TIM3->CCR3 = PWM_0;
			TIM3->CCR4 = PWM_0;
			break;
		} else if (aLeftButton == 1) {
			GPIOA->ODR &= (GPIOA->ODR ^ 2);
			GPIOA->ODR &= (GPIOA->ODR ^ 4);

			TIM3->CCR3 = PWM_0;
			TIM3->CCR4 = speed_20;
			continue;
		} else if (aRightButton == 1) {
			GPIOA->ODR &= (GPIOA->ODR ^ 2);
			GPIOA->ODR &= (GPIOA->ODR ^ 4);

			TIM3->CCR3 = speed_20;
			TIM3->CCR4 = PWM_0;
			continue;
		}

		if ((aLeft == 1) && (aRight == 1)) {
			*speed0 = speed_5;
			*speed1 = speed_2;
		} else if (aLeft == 1) {
			GPIOA->ODR &= (GPIOA->ODR ^ 2);
			GPIOA->ODR &= (GPIOA->ODR ^ 4);

			TIM3->CCR3 = *speed0;
			TIM3->CCR4 = *speed1;
		} else if (aRight == 1) {
			GPIOA->ODR &= (GPIOA->ODR ^ 2);
			GPIOA->ODR &= (GPIOA->ODR ^ 4);

			TIM3->CCR3 = *speed1;
			TIM3->CCR4 = *speed0;
		} else {
			GPIOA->ODR &= (GPIOA->ODR ^ 2);
			GPIOA->ODR &= (GPIOA->ODR ^ 4);

			TIM3->CCR3 = *speed0;
			TIM3->CCR4 = *speed0;
		}
	}
	char * done = DONE;
	print(done);
	delay_ms(1200);
}

void move_backButton(uint16_t* speed0, uint16_t* speed1) {
	while (1) {
		int bLeft = !(!(GPIOC->IDR & 4)); // Port C2
		int bRight = !(!(GPIOC->IDR & 8)); // Port C3

		int bLeftButton = !(!(GPIOC->IDR & 256)); // Port C8
		int bRightButton = !(!(GPIOC->IDR & 512)); // Port C9

		int leftSensor = !(!(GPIOC->IDR & 16)); // Port C4
		int rightSensor = !(!(GPIOC->IDR & 32)); // Port C5

		if ((bLeftButton == 1) && (bRightButton == 1)) {
			GPIOA->ODR |= 2;
			GPIOA->ODR |= 4;

			TIM3->CCR3 = PWM_0;
			TIM3->CCR4 = PWM_0;
			break;
		} else if (bLeftButton == 1) {
			GPIOA->ODR |= 2;
			GPIOA->ODR |= 4;

			TIM3->CCR3 = speed_20;
			TIM3->CCR4 = PWM_0;
			continue;
		} else if (bRightButton == 1) {
			GPIOA->ODR |= 2;
			GPIOA->ODR |= 4;

			TIM3->CCR3 = PWM_0;
			TIM3->CCR4 = speed_20;
			continue;
		}

		if ((bLeft == 1) && (bRight == 1)) {
			*speed0 = speed_5;
			*speed1 = speed_2;
		} else if (bLeft == 1) {
			GPIOA->ODR |= 2;
			GPIOA->ODR |= 4;

			TIM3->CCR3 = *speed1;
			TIM3->CCR4 = *speed0;
		} else if (bRight == 1) {
			GPIOA->ODR |= 2;
			GPIOA->ODR |= 4;

			TIM3->CCR3 = *speed0;
			TIM3->CCR4 = *speed1;
		} else {
			GPIOA->ODR |= 2;
			GPIOA->ODR |= 4;

			TIM3->CCR3 = *speed0;
			TIM3->CCR4 = *speed0;
		}
	}
	char * done = DONE;
	print(done);
	delay_ms(1000);
}

void small_move_forward() {
	GPIOA->ODR &= (GPIOA->ODR ^ 2);
	GPIOA->ODR &= (GPIOA->ODR ^ 4);

	TIM3->CCR3 = speed_5;
	TIM3->CCR4 = speed_5;
	delay_ms(800);
}

void small_move_back() {
	GPIOA->ODR |= 2;
	GPIOA->ODR |= 4;

	TIM3->CCR3 = speed_5;
	TIM3->CCR4 = speed_5;
	delay_ms(700);
}

void move_2forward(uint16_t* speed0, uint16_t* speed1) {
	int k = 0;
	while (1) {
		int aLeft = !(!(GPIOC->IDR & 1)); // Port C0
		int aRight = !(!(GPIOC->IDR & 2)); // Port C1

		int leftSensor = !(!(GPIOC->IDR & 16)); // Port C4
		int rightSensor = !(!(GPIOC->IDR & 32)); // Port C5

		if ((leftSensor == 1) && (rightSensor == 1)) {
			if (k == 0) {
				k = 1;
				delay_ms(200);
			} else {
				GPIOA->ODR &= (GPIOA->ODR ^ 2);
				GPIOA->ODR &= (GPIOA->ODR ^ 4);

				TIM3->CCR3 = PWM_0;
				TIM3->CCR4 = PWM_0;
				break;
			}
		}

		if ((aLeft == 1) && (aRight == 1)) {
			*speed0 = speed_5;
			*speed1 = speed_2;
		} else if (aLeft == 1) {
			GPIOA->ODR &= (GPIOA->ODR ^ 2);
			GPIOA->ODR &= (GPIOA->ODR ^ 4);

			TIM3->CCR3 = *speed0;
			TIM3->CCR4 = *speed1;
		} else if (aRight == 1) {
			GPIOA->ODR &= (GPIOA->ODR ^ 2);
			GPIOA->ODR &= (GPIOA->ODR ^ 4);

			TIM3->CCR3 = *speed1;
			TIM3->CCR4 = *speed0;
		} else {
			GPIOA->ODR &= (GPIOA->ODR ^ 2);
			GPIOA->ODR &= (GPIOA->ODR ^ 4);

			TIM3->CCR3 = *speed0;
			TIM3->CCR4 = *speed0;
		}
	}
	char * done = DONE;
	print(done);
	delay_ms(1000);
}

void move_back1(uint16_t* speed0, uint16_t* speed1) {
	while (1) {
		int bLeft = !(!(GPIOC->IDR & 4)); // Port C2
		int bRight = !(!(GPIOC->IDR & 8)); // Port C3

		int leftSensor = !(!(GPIOC->IDR & 16)); // Port C4
		int rightSensor = !(!(GPIOC->IDR & 32)); // Port C5

		if ((leftSensor == 1) && (rightSensor == 1)) {
			GPIOA->ODR |= 2;
			GPIOA->ODR |= 4;

			TIM3->CCR3 = PWM_0;
			TIM3->CCR4 = PWM_0;
			break;
		}

		if ((bLeft == 1) && (bRight == 1)) {
			*speed0 = speed_5;
			*speed1 = speed_2;
		} else if (bLeft == 1) {
			GPIOA->ODR |= 2;
			GPIOA->ODR |= 4;

			TIM3->CCR3 = *speed1;
			TIM3->CCR4 = *speed0;
		} else if (bRight == 1) {
			GPIOA->ODR |= 2;
			GPIOA->ODR |= 4;

			TIM3->CCR3 = *speed0;
			TIM3->CCR4 = *speed1;
		} else {
			GPIOA->ODR |= 2;
			GPIOA->ODR |= 4;

			TIM3->CCR3 = *speed0;
			TIM3->CCR4 = *speed0;
		}
	}
	char * done = DONE;
	print(done);
	delay_ms(1400);
}

void move_back(uint16_t* speed0, uint16_t* speed1) {
	while (1) {
		int bLeft = !(!(GPIOC->IDR & 4)); // Port C0
		int bRight = !(!(GPIOC->IDR & 8)); // Port C1

		int leftSensor = !(!(GPIOC->IDR & 16)); // Port C4
		int rightSensor = !(!(GPIOC->IDR & 32)); // Port C5

		if ((leftSensor == 1) && (rightSensor == 1)) {
			GPIOA->ODR |= 2;
			GPIOA->ODR |= 4;

			TIM3->CCR3 = PWM_0;
			TIM3->CCR4 = PWM_0;
			break;
		}

		if ((bLeft == 1) && (bRight == 1)) {
			*speed0 = speed_5;
			*speed1 = speed_2;
		} else if (bLeft == 1) {
			GPIOA->ODR |= 2;
			GPIOA->ODR |= 4;

			TIM3->CCR3 = *speed0;
			TIM3->CCR4 = *speed1;
		} else if (bRight == 1) {
			GPIOA->ODR |= 2;
			GPIOA->ODR |= 4;

			TIM3->CCR3 = *speed1;
			TIM3->CCR4 = *speed0;
		} else {
			GPIOA->ODR |= 2;
			GPIOA->ODR |= 4;

			TIM3->CCR3 = *speed0;
			TIM3->CCR4 = *speed0;
		}
	}

	char * done = DONE;
	print(done);
	delay_ms(1000);
}

void turnLeft(uint16_t* speed0, uint16_t* speed1) {
	GPIOA->ODR &= (GPIOA->ODR ^ 2);
	GPIOA->ODR |= 4;

	TIM3->CCR3 = *speed0;
	TIM3->CCR4 = *speed0;
	delay_ms(200);

	while (1) {
		int aLeft = !(!(GPIOC->IDR & 1)); // Port C0
		int aRight = !(!(GPIOC->IDR & 2)); // Port C1

		int leftSensor = !(!(GPIOC->IDR & 16)); // Port C4
		int rightSensor = !(!(GPIOC->IDR & 32)); // Port C5

		if (aLeft == 1) {
			GPIOA->ODR &= (GPIOA->ODR ^ 2);
			GPIOA->ODR |= 4;

			TIM3->CCR3 = PWM_0;
			TIM3->CCR4 = PWM_0;
			break;
		} else {
			GPIOA->ODR &= (GPIOA->ODR ^ 2);
			GPIOA->ODR |= 4;

			TIM3->CCR3 = *speed0;
			TIM3->CCR4 = *speed0;
		}
	}

	char * done = DONE;
	print(done);
	delay_ms(1000);
}

void turnRight(uint16_t* speed0, uint16_t* speed1) {
	while (1) {
		int aLeft = !(!(GPIOC->IDR & 1)); // Port C0
		int aRight = !(!(GPIOC->IDR & 2)); // Port C1

		int leftSensor = !(!(GPIOC->IDR & 16)); // Port C4
		int rightSensor = !(!(GPIOC->IDR & 32)); // Port C5

		if (aRight == 1) {
			GPIOA->ODR |= 2;
			GPIOA->ODR &= (GPIOA->ODR ^ 4);

			TIM3->CCR3 = PWM_0;
			TIM3->CCR4 = PWM_0;
			break;
		} else {
			GPIOA->ODR |= 2;
			GPIOA->ODR &= (GPIOA->ODR ^ 4);

			TIM3->CCR3 = *speed0;
			TIM3->CCR4 = *speed0;
		}
	}

	char * done = DONE;
	print(done);
	delay_ms(1000);
}

void turnBackLeft(uint16_t* speed0, uint16_t* speed1) {
	GPIOA->ODR &= (GPIOA->ODR ^ 2);
	GPIOA->ODR |= 4;

	TIM3->CCR3 = *speed0;
	TIM3->CCR4 = *speed0;
	delay_ms(200);
	while (1) {
		int bLeft = !(!(GPIOC->IDR & 4)); // Port C0
		int bRight = !(!(GPIOC->IDR & 8)); // Port C1

		int leftSensor = !(!(GPIOC->IDR & 16)); // Port C4
		int rightSensor = !(!(GPIOC->IDR & 32)); // Port C5

		if (bLeft == 1) {
			GPIOA->ODR &= (GPIOA->ODR ^ 2);
			GPIOA->ODR |= 4;

			TIM3->CCR3 = PWM_0;
			TIM3->CCR4 = PWM_0;
			break;
		} else {
			GPIOA->ODR &= (GPIOA->ODR ^ 2);
			GPIOA->ODR |= 4;

			TIM3->CCR3 = *speed0;
			TIM3->CCR4 = *speed0;
		}
	}

	char * done = DONE;
	print(done);
	delay_ms(1000);
}

void turnBackRight(uint16_t* speed0, uint16_t* speed1) {
	GPIOA->ODR |= 2;
	GPIOA->ODR &= (GPIOA->ODR ^ 4);

	TIM3->CCR3 = *speed0;
	TIM3->CCR4 = *speed0;
	delay_ms(300);
	while (1) {
		int bLeft = !(!(GPIOC->IDR & 4)); // Port C0
		int bRight = !(!(GPIOC->IDR & 8)); // Port C1

		int leftSensor = !(!(GPIOC->IDR & 16)); // Port C4
		int rightSensor = !(!(GPIOC->IDR & 32)); // Port C5

		if (bRight == 1) {
			GPIOA->ODR |= 2;
			GPIOA->ODR &= (GPIOA->ODR ^ 4);

			TIM3->CCR3 = PWM_0;
			TIM3->CCR4 = PWM_0;
			break;
		} else {
			GPIOA->ODR |= 2;
			GPIOA->ODR &= (GPIOA->ODR ^ 4);

			TIM3->CCR3 = *speed0;
			TIM3->CCR4 = *speed0;
		}
	}
	delay_ms(1000);

	char * done = DONE;
	print(done);

}

void stop() {
	TIM3->CCR3 = PWM_0;
	TIM3->CCR4 = PWM_0;
	char* done = DONE;
	print(done);
}

void planC() {
	int k = 0;
	while (1) {
		int aLeft1 = !(!(GPIOC->IDR & 1)); // Port C0   0000 0000 0000 0001
		int aRight2 = !(!(GPIOC->IDR & 2)); // Port C1  0000 0000 0000 0010
		int bLeft3 = !(!(GPIOC->IDR & 4)); // Port C2   0000 0000 0000 0100
		int bRight4 = !(!(GPIOC->IDR & 8)); // Port C3
		int cLeft5 = !(!(GPIOC->IDR & 16)); // Port C4
		int cRight6 = !(!(GPIOC->IDR & 32)); // Port C5

		if (((aLeft1 == 1) || (bRight4 == 1)) && (k == 1)) {
			char* done = "DONE\n";
			print(done);
			TIM3->CCR3 = PWM_0;
			TIM3->CCR4 = PWM_0;
			TIM4->CCR3 = PWM_0;
			return;
		}

		if ((cLeft5 == 1) && (cRight6 == 1)) {

			k = 1;
		} else if (cRight6 == 1) {
			GPIOA->ODR &= (GPIOA->ODR ^ 2);
			GPIOA->ODR |= 4;
			GPIOA->ODR |= 8;

			TIM3->CCR3 = PWM_10;
			TIM3->CCR4 = PWM_0;
			TIM4->CCR3 = PWM_20;
		} else if (cLeft5 == 1) {
			GPIOA->ODR &= (GPIOA->ODR ^ 2);
			GPIOA->ODR |= 4;
			GPIOA->ODR |= 8;

			TIM3->CCR3 = PWM_20;
			TIM3->CCR4 = PWM_0;
			TIM4->CCR3 = PWM_10;
		} else {
			GPIOA->ODR &= (GPIOA->ODR ^ 2);
			GPIOA->ODR |= 4;
			GPIOA->ODR |= 8;

			TIM3->CCR3 = PWM_20;
			TIM3->CCR4 = PWM_0;
			TIM4->CCR3 = PWM_20;
		}
	}
	char * done = DONE;
	print(done);
}
