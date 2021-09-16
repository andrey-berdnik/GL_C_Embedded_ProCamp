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

static H_HAL_trigger_CB MotorSpeedOff;
static H_HAL_trigger_CB MotorLowSpeedDown;
static H_HAL_trigger_CB MotorLowSpeedUp;

static H_HAL_trigger_CB FloorChanged;
static H_HAL_trigger_CB PositionChanged;

void processLimitSwitchesCabinFloorHigh()
{

    current_position = e_CabinPositionHigh;
    PositionChanged();
}

void processLimitSwitchesCabinFloor()
{
    if (current_floor == 0)
    {
        current_floor = 1;
        MotorSpeedOff();
        CabinBrackeEnable();
    }
    else
    {

        if (current_position == e_CabinPositionLow && current_floor < 3)
        {
            current_floor++;
            FloorChanged();
        }

        if (current_position == e_CabinPositionHigh && current_floor > 1)
        {
            current_floor--;
            FloorChanged();
        }

        current_position = e_CabinPositionFloor;
        PositionChanged();
    }
}

void processLimitSwitchesCabinFloorLow()
{
    if (current_floor != 0)
    {
        current_position = e_CabinPositionLow;
        PositionChanged();
    }
}

void CabinSet(int floor, positionType state)
{

    current_floor = floor;
    current_position = state;
}

void processLimitSwitchesCabinMax()
{
    MotorSpeedOff();
    CabinBrackeEnable();
    CabinSet(4, e_CabinPositionMax);
}

void processLimitSwitchesCabinMin()
{
    //  MotorSpeedOff();
    CabinSet(0, e_CabinPositionMin);
    MotorLowSpeedUp();
}

void CabinInit(H_HAL_trigger_CB MotorSpeedOff_CB,
               H_HAL_trigger_CB MotorLowSpeedDown_CB,
               H_HAL_trigger_CB MotorLowSpeedUp_CB,
               H_HAL_trigger_CB FloorChanged_CB,
               H_HAL_trigger_CB PositionChanged_CB)
{
    MotorSpeedOff = MotorSpeedOff_CB;
    MotorLowSpeedDown = MotorLowSpeedDown_CB;
    MotorLowSpeedUp = MotorLowSpeedUp_CB;

    FloorChanged = FloorChanged_CB;
    PositionChanged = PositionChanged_CB;

    HAL_LimitSwitchesCabinFloorHigh_set(processLimitSwitchesCabinFloorHigh);
    HAL_LimitSwitchesCabinFloor_CB_set(processLimitSwitchesCabinFloor);
    HAL_LimitSwitchesCabinFloorLow_CB_set(processLimitSwitchesCabinFloorLow);

    HAL_LimitSwitchesCabinMax_CB_set(processLimitSwitchesCabinMax);
    HAL_LimitSwitchesCabinMin_CB_set(processLimitSwitchesCabinMin);

    CabinBrakeStatus = e_CabinBrackeEnable;
    HAL_CabinBrakesOn();

    CabinSet(1, e_CabinPositionUknow);
}

void CabinMaping()
{
    CabinBrackeDisable();
    MotorLowSpeedDown();
}

int CabinGetCurrentFloor()
{
    return current_floor;
}

positionType CabinGetCurrenPosition()
{
    return current_position;
}
