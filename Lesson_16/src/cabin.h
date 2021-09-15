#ifndef  H_CABIN
#define H_CABIN

#include "hal.h"
typedef enum
{
    e_CabinBrackeUknow,
    e_CabinBrackeEnable,
    e_CabinBrackeDisable
} cState;

void CabinBrackeEnable();
void CabinBrackeDisable();

cState CabinBrackeGetStatus();


typedef enum
{
    e_CabinPositionUknow,
    e_CabinPositionMin,
    e_CabinPositionLow,
    e_CabinPositionFloor,
    e_CabinPositionHigh,
    e_CabinPositionMax
} positionType;



void CabinInit(H_HAL_trigger_CB MotorSpeedOff_CB,
               H_HAL_trigger_CB MotorLowSpeedDown_CB);

void CabinSet(int floor, positionType state);
int CabinGetCurrentFloor();
positionType CabinGetCurrenPosition();

void CabinMaping();



#endif