#ifndef H_CABIN
#define H_CABIN
#include "hal.h"

typedef enum
{
    e_CabinBrackeUknow,
    e_CabinBrackeEnable,
    e_CabinBrackeDisable
} cState;

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
               H_HAL_trigger_CB MotorLowSpeedDown_CB,
               H_HAL_trigger_CB MotorLowSpeedUp_CB,
               H_HAL_trigger_CB FloorChanged,
               H_HAL_trigger_CB StateChanged);

void CabinBrackeEnable(void);
void CabinBrackeDisable(void);
void CabinSet(int floor, positionType state);
void CabinMaping(void);

int CabinGetCurrentFloor(void);
cState CabinBrackeGetStatus(void);
positionType CabinGetCurrenPosition(void);

#endif //H_CABIN