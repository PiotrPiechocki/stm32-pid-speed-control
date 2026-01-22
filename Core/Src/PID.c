/*
 * PID.c
 *
 *  Created on: Jan 18, 2026
 *      Author: Szymon
 */

#include "PID.h"
#include <math.h>

void PID_Init(PID_Motor *pid, float Kp, float Ki, float Kd, float dt)
{
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->dt = dt;
    pid->target = 0.0f;
    pid->integral = 0.0f;
    pid->last_error = 0.0f;
    pid->output = 0.0f;
}

void PID_SetTarget(PID_Motor *pid, float target)
{
    pid->target = target;
}

void PID_Update(PID_Motor *pid, float current_rpm)
{
    float abs_target  = fabs(pid->target);
    float abs_current = fabs(current_rpm);

    float error = abs_target - abs_current;

    /* === ZEROWANIE CAŁKI === */

    // 1. zmiana kierunku
    if ((pid->prev_target >= 0.0f && pid->target < 0.0f) ||
        (pid->prev_target < 0.0f  && pid->target >= 0.0f))
    {
        pid->integral = 0.0f;
    }

    // 2. zadana prędkość = 0
    if (abs_target < 0.1f)
    {
        pid->integral = 0.0f;
        pid->output = 0.0f;
        pid->last_error = error;
        pid->prev_target = pid->target;
        return;
    }

    /* === CAŁKA === */
    pid->integral += error * pid->dt;



    /* === POCHODNA === */
    float derivative = (error - pid->last_error) / pid->dt;

    /* === WYJŚCIE PID === */
    pid->output = pid->Kp * error
                + pid->Ki * pid->integral
                + pid->Kd * derivative;

    /* === OGRANICZENIE PWM === */
    if (pid->output > 100.0f) pid->output = 100.0f;
    if (pid->output < 0.0f)   pid->output = 0.0f;

    pid->last_error  = error;
    pid->prev_target = pid->target;
}

float PID_GetPWM(PID_Motor *pid)
{
    return pid->output;
}
