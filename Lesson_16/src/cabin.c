#include "cabin.h"
#include "hal.h"

static cState CabinBrakeStatus = e_CabinBrackeUknow;
static int current_floor = 1;
static positionType current_position = e_CabinPositionUknow;

void CabinBrackeEnable()
{
    if (CabinBrakeStatus != e_CabinBrackeEnable)
    {
        CabinBrakeStatus = e_CabinBrackeEnable;
        HAL_CabinBrakesOn();
    }
}

void CabinBrackeDisable()
{
    if (CabinBrakeStatus != e_CabinBrackeDisable)
    {
        CabinBrakeStatus = e_CabinBrackeDisable;
        HAL_CabinBrakesOff();
    }
}

cState CabinBrackeGetStatus()
{
    return CabinBrakeStatus;
}

void processLimitSwitchesCabinFloorHigh()
{

    if (current_position == e_CabinPositionLow && current_floor > 1)
    {
        current_floor--;
    }
    current_position = e_CabinPositionHigh;
}

void processLimitSwitchesCabinFloor()
{
    current_position = e_CabinPositionFloor;
}

void processLimitSwitchesCabinFloorLow()
{
    if (current_position == e_CabinPositionHigh && current_floor < 3)
    {
        current_floor++;
    }
    current_position = e_CabinPositionLow;
}

void CabinSet(int floor, positionType state)
{

    current_floor = floor;
    current_position = state;
}

void CabinInit()
{

    HAL_LimitSwitchesCabinFloorHigh_set(processLimitSwitchesCabinFloorHigh);
    HAL_LimitSwitchesCabinFloor_CB_set(processLimitSwitchesCabinFloor);
    HAL_LimitSwitchesCabinFloorLow_CB_set(processLimitSwitchesCabinFloorLow);

    HAL_LimitSwitchesCabinMax_CB_set(processLimitSwitchesCabinMax);
    HAL_LimitSwitchesCabinMin_CB_set(processLimitSwitchesCabinMin);

    CabinBrakeStatus = e_CabinBrackeEnable;
    HAL_CabinBrakesOn();

    CabinSet(1, e_CabinPositionUknow);
}

int CabinGetCurrentFloor()
{
    return current_floor;
}

void processLimitSwitchesCabinMax()
{
    MotorSpeedOff();
    CabinBrackeEnable();
    CabinInit(4, e_CabinPositionMax);
    QueueDrop();
    QueueAppend(3);
}

void processLimitSwitchesCabinMin()
{
    MotorSpeedOff();
    CabinBrackeEnable();
    CabinSet(0, e_CabinPositionMin);
    QueueDrop();
    QueueAppend(1);
}