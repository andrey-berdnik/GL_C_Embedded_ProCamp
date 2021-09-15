#include "motor.h"
#include "hal.h"

mState motorState = e_MotorSpeedOff;

mState MotorGetState()
{
    return motorState;
}

void MotorLowSpeedUp()
{
    if (motorState != e_MotorLowSpeedUp)
    {
        motorState = e_MotorLowSpeedUp;
        HAL_MotorLowSpeedUp();
    }
}
void MotorHighSpeedUp()
{
    if (motorState != e_MotorHighSpeedUp)
    {
        motorState = e_MotorHighSpeedUp;
        HAL_MotorHighSpeedUp();
    }
}
void MotorLowSpeedDown()
{
    if (motorState != e_MotorLowSpeedDown)
    {
        motorState = e_MotorLowSpeedDown;
        HAL_MotorLowSpeedDown();
    }
}
void MotorHighSpeedDown()
{
    if (motorState != e_MotorHighSpeedDown)
    {
        motorState = e_MotorHighSpeedDown;
        HAL_MotorHighSpeedDown();
    }
}
void MotorSpeedOff()
{
    if (motorState != e_MotorSpeedOff)
    {
        motorState = e_MotorSpeedOff;
        HAL_MotorSpeedOff();
    }
}

void MotorInit()
{
    motorState = e_MotorSpeedOff;
    HAL_MotorSpeedOff();
}