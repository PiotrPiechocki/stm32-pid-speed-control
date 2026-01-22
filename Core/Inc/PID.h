/*
 * PID.h
 *
 *  Created on: Jan 18, 2026
 *      Author: Szymon
 */

#ifndef PID_MOTOR_H
#define PID_MOTOR_H

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    float Kp;
    float Ki;
    float Kd;

    float target;       // żądana prędkość (może być ujemna)
    float integral;
    float last_error;
    float output;       // ostatnie wyjście PID (0-100)
    float dt;
    float prev_target;
    float integral_limit;
    // czas próbkowania w sekundach
} PID_Motor;

// inicjalizacja PID
void PID_Init(PID_Motor *pid, float Kp, float Ki, float Kd, float dt);

// ustawienie docelowej prędkości
void PID_SetTarget(PID_Motor *pid, float target);

// aktualizacja PID z aktualną prędkością
void PID_Update(PID_Motor *pid, float current_rpm);

// pobranie wartości PWM (0-100)
float PID_GetPWM(PID_Motor *pid);

#endif
