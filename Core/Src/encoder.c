/*
 * encoder.c
 *
 *  Created on: Jan 17, 2026
 *      Author: Szymon
 */
#include "encoder.h"
/*
void update_encoder(encoder *encoder_val, TIM_HandleTypeDef *htim)
{
	uint32_t temporary_count = __HAL_TIM_GET_COUNTER(htim);
	static uint8_t start_time = 0;

	if(!start_time)
	{
		encoder_val -> velocity = 0;
		start_time = 1;
	}
	else
	{
		if(temporary_count == encoder_val -> last_count_val)
		{
			encoder_val -> velocity = 0;
		}
		else if(temporary_count > encoder_val -> last_count_val)
		{
			if(__HAL_TIM_IS_TIM_COUNTING_DOWN(htim))
			{
				encoder_val -> velocity = -encoder_val -> last_count_val - (__HAL_TIM_GET_AUTORELOAD(htim) - temporary_count);
			}
			else
			{
				encoder_val -> velocity = temporary_count - encoder_val -> last_count_val;
			}
		}
		else
		{
			if(__HAL_TIM_IS_TIM_COUNTING_DOWN(htim))
			{
				encoder_val -> velocity = temporary_count - encoder_val -> last_count_val;
			}
			else
			{
				encoder_val -> velocity = temporary_count + (__HAL_TIM_GET_AUTORELOAD(htim) - encoder_val -> last_count_val);
			}
		}
	}
	encoder_val -> position += encoder_val -> velocity;
	encoder_val -> last_count_val = temporary_count;
}

void reset_encoder(encoder *encoder_val)
{
	encoder_val -> velocity = 0;
	encoder_val -> position = 0;
	encoder_val -> last_count_val = 0;
}
*/

#include "encoder.h"



void encoder_init(encoder *enc, TIM_HandleTypeDef *htim)
{
    enc->position = 0;
    enc->velocity = 0;
    enc->last_count_val = (int32_t)__HAL_TIM_GET_COUNTER(htim);

}



#define VEL_BUF_SIZE 20
#define ENC_PPR 823.1f
#define ENC_PPR_EFFECTIVE (ENC_PPR * 4)
#define Ts 0.05
static int32_t vel_buf[VEL_BUF_SIZE];
static uint8_t vel_idx = 0;

void encoder_update(encoder *enc, TIM_HandleTypeDef *htim)
{
    int32_t cnt = (int32_t)__HAL_TIM_GET_COUNTER(htim);
    int32_t diff = cnt - enc->last_count_val;

    // obsługa przepełnienia 16-bit licznika
    if (diff > 32767) diff -= 65536;
    else if (diff < -32768) diff += 65536;

    enc->position += diff;

    // zapis do bufora
    vel_buf[vel_idx++] = diff;
    if (vel_idx >= VEL_BUF_SIZE) vel_idx = 0;

    // suma impulsów w buforze
    int32_t sum = 0;
    for (int i = 0; i < VEL_BUF_SIZE; i++)
        sum += vel_buf[i];

    enc->velocity = sum;

    // przeliczenie na RPM
    enc->rpm = ((float)enc->velocity / ENC_PPR_EFFECTIVE) * (60.0f / (VEL_BUF_SIZE * Ts*0.1));

    enc->last_count_val = cnt;
}

void encoder_reset(encoder *enc)
{
    enc->position = 0;
    enc->velocity = 0;
}
