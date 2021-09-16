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

mState MotorGetState(void);

void MotorLowSpeedUp(void);
void MotorHighSpeedUp(void);
void MotorLowSpeedDown(void);
void MotorHighSpeedDown(void);
void MotorSpeedOff(void);
void MotorInit(void);



#endif //H_MOTOR