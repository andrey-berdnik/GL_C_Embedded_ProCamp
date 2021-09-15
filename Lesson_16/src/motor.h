#ifndef H_MOTOR
#define H_MOTOR
typedef enum
{
    e_MotorSpeedOff = 0,
    e_MotorLowSpeedUp = 1,
    e_MotorHighSpeedUp,
    e_MotorLowSpeedDown,
    e_MotorHighSpeedDown
} mState;

mState MotorGetState();

void MotorLowSpeedUp();
void MotorHighSpeedUp();
void MotorLowSpeedDown();
void MotorHighSpeedDown();
void MotorSpeedOff();
void MotorInit();



#endif