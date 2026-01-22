/*
 * encoder.h
 *
 *  Created on: Jan 17, 2026
 *      Author: Szymon
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_
#include "main.h"
#include "stdint.h"

typedef struct{
	int16_t velocity;
	int64_t position;
	uint32_t last_count_val;
float rpm;
}encoder;

void encoder_init(encoder *enc, TIM_HandleTypeDef *htim);

void update_encoder(encoder *enc, TIM_HandleTypeDef *htim);

void reset_encoder(encoder *enc);




#endif /* INC_ENCODER_H_ */
