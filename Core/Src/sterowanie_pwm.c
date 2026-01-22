/*
 * sterowanie_pwm.c
 *
 *  Created on: Jan 13, 2026
 *      Author: Szymon
 *
 *
 *
 *
 */


#include "sterowanie_pwm.h"

static TIM_HandleTypeDef *motor_htim;
static uint32_t motor_ch1;
static uint32_t motor_ch3;


void Motor_Init(TIM_HandleTypeDef *htim, uint32_t channel1, uint32_t channel3)
{
    motor_htim = htim;
    motor_ch1 = channel1;
    motor_ch3 = channel3;


    __HAL_TIM_SET_COMPARE(motor_htim, motor_ch1, 0);
    __HAL_TIM_SET_COMPARE(motor_htim, motor_ch3, 0);
    HAL_TIM_PWM_Start(motor_htim, motor_ch1);
    HAL_TIM_PWM_Start(motor_htim, motor_ch3);
}



void set_PWM(DIRECTION direction,uint8_t speed)
{

 if(speed > 100) speed = 100;

 uint32_t pulse = (motor_htim->Init.Period + 1) * speed / 100;

 switch(direction)
     {
         case FORWARD:
             __HAL_TIM_SET_COMPARE(motor_htim, motor_ch1, pulse);
             __HAL_TIM_SET_COMPARE(motor_htim, motor_ch3, 0);
             break;

         case BACKWARD:
             __HAL_TIM_SET_COMPARE(motor_htim, motor_ch1, 0);
             __HAL_TIM_SET_COMPARE(motor_htim, motor_ch3, pulse);
             break;

         case STOP:
         default:
             __HAL_TIM_SET_COMPARE(motor_htim, motor_ch1, 0);
             __HAL_TIM_SET_COMPARE(motor_htim, motor_ch3, 0);
             break;
     }



}
