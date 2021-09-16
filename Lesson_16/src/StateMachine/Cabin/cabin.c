#include "cabin.h"
#include "hal.h"

static cState CabinBrakeStatus = e_CabinBrackeUknow;
static int current_floor = 1;
static positionType current_position = e_CabinPositionUknow;

static H_HAL_trigger_CB MotorSpeedOff;
static H_HAL_trigger_CB MotorLowSpeedDown;
static H_HAL_trigger_CB MotorLowSpeedUp;
static H_HAL_trigger_CB FloorChanged;
static H_HAL_trigger_CB PositionChanged;

static void processLimitSwitchesCabinFloorHigh(void);
static void processLimitSwitchesCabinFloor(void);
static void processLimitSwitchesCabinFloorLow(void);
static void processLimitSwitchesCabinMax(void);
static void processLimitSwitchesCabinMin(void);

void CabinBrackeEnable(void)
{
    if (CabinBrakeStatus != e_CabinBrackeEnable)
    {
        CabinBrakeStatus = e_CabinBrackeEnable;
        HAL_CabinBrakesOn();
    }
}

void CabinBrackeDisable(void)
{
    if (CabinBrakeStatus != e_CabinBrackeDisable)
    {
        CabinBrakeStatus = e_CabinBrackeDisable;
        HAL_CabinBrakesOff();
    }
}

cState CabinBrackeGetStatus(void)
{
    return CabinBrakeStatus;
}

static void processLimitSwitchesCabinFloorHigh(void)
{

    current_position = e_CabinPositionHigh;
    PositionChanged();
}

static void processLimitSwitchesCabinFloor(void)
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

static void processLimitSwitchesCabinFloorLow(void)
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

static void processLimitSwitchesCabinMax(void)
{
    MotorSpeedOff();
    CabinBrackeEnable();
    CabinSet(4, e_CabinPositionMax);
}

static void processLimitSwitchesCabinMin(void)
{
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

void CabinMaping(void)
{
    CabinBrackeDisable();
    MotorLowSpeedDown();
}

int CabinGetCurrentFloor(void)
{
    return current_floor;
}

positionType CabinGetCurrenPosition(void)
{
    return current_position;
}
