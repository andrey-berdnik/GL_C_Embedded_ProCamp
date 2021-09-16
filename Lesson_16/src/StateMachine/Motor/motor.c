#include "motor.h"
#include "hal.h"

mState motorState = e_MotorSpeedOff;

mState MotorGetState(void)
{
    return motorState;
}

void MotorLowSpeedUp(void)
{
    if (motorState != e_MotorLowSpeedUp)
    {
        motorState = e_MotorLowSpeedUp;
        HAL_MotorLowSpeedUp();
    }
}
void MotorHighSpeedUp(void)
{
    if (motorState != e_MotorHighSpeedUp)
    {
        motorState = e_MotorHighSpeedUp;
        HAL_MotorHighSpeedUp();
    }
}
void MotorLowSpeedDown(void)
{
    if (motorState != e_MotorLowSpeedDown)
    {
        motorState = e_MotorLowSpeedDown;
        HAL_MotorLowSpeedDown();
    }
}
void MotorHighSpeedDown(void)
{
    if (motorState != e_MotorHighSpeedDown)
    {
        motorState = e_MotorHighSpeedDown;
        HAL_MotorHighSpeedDown();
    }
}
void MotorSpeedOff(void)
{
    if (motorState != e_MotorSpeedOff)
    {
        motorState = e_MotorSpeedOff;
        HAL_MotorSpeedOff();
    }
}

void MotorInit(void)
{
    motorState = e_MotorSpeedOff;
    HAL_MotorSpeedOff();
}