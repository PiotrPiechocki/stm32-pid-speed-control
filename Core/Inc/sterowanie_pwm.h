/*
 * sterowanie_pwm.h
 *
 *  Created on: Jan 13, 2026
 *      Author: Szymon
 */

#ifndef INC_STEROWANIE_PWM_H_
#define INC_STEROWANIE_PWM_H_

#include "stm32f7xx_hal.h"
#include <stdint.h>


typedef enum{
	STOP = 0,
	FORWARD,
	BACKWARD
}DIRECTION;

void Motor_Init(TIM_HandleTypeDef *htim, uint32_t channel1, uint32_t channel3);

void set_PWM(DIRECTION direction,uint8_t speed);



#endif /* INC_STEROWANIE_PWM_H_ */


